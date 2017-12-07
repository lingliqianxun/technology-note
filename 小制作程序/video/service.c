//#视频监控#
//2014年9月30日
//By绫里千寻
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
#include<netdb.h>
#include<signal.h>
#include<linux/videodev2.h>
#include<sys/ioctl.h>
#include<sys/mman.h>
#include"print.h"
#define DHT_SIZE 432

typedef struct VideoBuffer{
	void *start;
	size_t length;
}VideoBuffer;
VideoBuffer *buffers;
struct v4l2_requestbuffers req;
struct v4l2_buffer buf;
int socketfd;
int cameraFd;
char *frame_buf1=NULL;
char *frame_buf2=NULL;
ssize_t buf_size;
pthread_mutex_t mutex;

void signal_handler(int signo){
	if(signo==SIGINT){
		close(socketfd);
		//关闭视频显示
		int type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if(ioctl(cameraFd,VIDIOC_STREAMOFF,&type)==-1){
			fprintf(stderr,"ioctl VIDIOC_STREAMON:%s\n",strerror(errno));
			exit(1);
		}
		close(cameraFd);
		free(buffers);
		free(frame_buf1);
		free(frame_buf2);
		printf("service will be closed!\n");
		exit(1);
	}
	if(signo==SIGPIPE){
		printf("客户端已下线！\n");
	}
}
void out_client(struct sockaddr_in clientaddr){
	char buf[16]={'\0'};
	inet_ntop(AF_INET,&(clientaddr.sin_addr.s_addr),buf,16);
	int port=ntohs(clientaddr.sin_port);
	printf("client ip:%s port:%d \n",buf,port);
}
void init_camera(){
	if(cameraFd<0){
		fprintf(stderr,"open:%s\n",strerror(errno));
		exit(1);
	}
	//检查支持的标准
	v4l2_std_id std;
	int ret;
	do{
		ret=ioctl(cameraFd,VIDIOC_QUERYSTD,&std);
	}while(ret==-1&&errno==EAGAIN);
	switch(std){
		case V4L2_STD_NTSC:
			printf("V4L2_STD_NTSC\n");
		case V4L2_STD_PAL:
			printf("V4L2_STD_PAL\n");
		default:
			printf("other\n");
	}
	//设置视频捕获格式
	struct v4l2_format fmt;
	memset(&fmt,0,sizeof(fmt));
	fmt.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;//数据流类型
	fmt.fmt.pix.width=720;//16整数倍
	fmt.fmt.pix.height=576;//16整数倍
	fmt.fmt.pix.pixelformat=V4L2_PIX_FMT_YUYV;//视频数据存储类型YUYV/MJPEG
	fmt.fmt.pix.field=V4L2_FIELD_INTERLACED;
	if(ioctl(cameraFd,VIDIOC_S_FMT,&fmt)==-1){
		fprintf(stderr,"ioctl VIDIOC_S_FMT:%s\n",strerror(errno));
		exit(1);
	}
	//分配内存
	memset(&req,0,sizeof(req));
	req.count=5;//缓存数量
	req.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;//数据流类型
	req.memory=V4L2_MEMORY_MMAP;//视频采集方式
	if(ioctl(cameraFd,VIDIOC_REQBUFS,&req)==-1){
		fprintf(stderr,"ioctl VIDIOC_REQBUFS:%s\n",strerror(errno));
		exit(1);
	}
	//开始视频显示
	int type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(ioctl(cameraFd,VIDIOC_STREAMON,&type)==-1){
		fprintf(stderr,"ioctl VIDIOC_STREAMON:%s\n",strerror(errno));
		exit(1);
	}
	//获取并记录缓存的物理空间
	buffers=(VideoBuffer*)calloc(req.count,sizeof(*buffers));
	int numBufs;
	for(numBufs=0;numBufs<req.count;numBufs++){
		memset(&buf,0,sizeof(buf));
		buf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;//数据流类型
		buf.memory=V4L2_MEMORY_MMAP;//视频采集方式
		buf.index=numBufs;
		//读取缓存
		if(ioctl(cameraFd,VIDIOC_QUERYBUF,&buf)==-1){
			fprintf(stderr,"ioctl VIDIOC_QUERYBUF:%s\n",strerror(errno));
			exit(1);
		}
		buffers[numBufs].length=buf.length;
		//转换成相对地址
		buffers[numBufs].start=mmap(NULL,buf.length,PROT_READ|PROT_WRITE,MAP_SHARED,cameraFd,buf.m.offset);
		if(buffers[numBufs].start==MAP_FAILED){
			fprintf(stderr,"mmap:%s\n",strerror(errno));
			exit(1);
		}
		//放入缓存队列
		if(ioctl(cameraFd,VIDIOC_QBUF,&buf)==-1){
			fprintf(stderr,"ioctl VIDIOC_QBUF:%s\n",strerror(errno));
			exit(1);
		}
	}
}

int getframe(){
	memset(&buf,0,sizeof(buf));
	buf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;//数据流类型
	buf.memory=V4L2_MEMORY_MMAP;//视频采集方式
	buf.index=0;
	//读取缓存
	if(ioctl(cameraFd,VIDIOC_DQBUF,&buf)==-1){
		fprintf(stderr,"ioctl VIDIOC_DQBUF:%s\n",strerror(errno));
		return -1;;
	}
	//格式转换
	//printf("buf.length: %d\n", buf.length);
	buf_size=buf.bytesused;
	unsigned char *tmp=(char*)malloc(buf.bytesused);
	memset(tmp,0,buf.bytesused);
	yuv_to_jpeg((unsigned char*)buffers[buf.index].start,tmp,buf.bytesused,100);
	//存放1级缓存
	if(frame_buf1==NULL)
		frame_buf1=(char*)malloc(buf_size);
	memcpy(frame_buf1,tmp,buf_size);
	free(tmp);
	//重新放入缓存队列
	if(ioctl(cameraFd,VIDIOC_QBUF,&buf)==-1){
		fprintf(stderr,"ioctl VIDIOC_QBUF:%s\n",strerror(errno));
		return -1;
	}
	return 0;
}

void* th_fun2(void*arg){
	while(1){
		if(getframe()<0){
			printf("getfram failed!\n");
			pthread_exit((void*)0);
		}
		if(frame_buf2==NULL)
			frame_buf2=(char*)malloc(buf_size);
		pthread_mutex_lock(&mutex);
		memcpy(frame_buf2,frame_buf1,buf_size);
		pthread_mutex_unlock(&mutex);
		usleep(10000);
	}
}
void* th_fun1(void*arg){
	int fd=(int)arg;
	char buffer[1024];
	memset(buffer,0,sizeof(buffer));
	read(fd,buffer,sizeof(buffer));
	char reponse[] = "HTTP/1.0 200 OK\r\nConnection: close\r\nServer: Net-camera-1-0\r\nCache-Control: no-store, no-cache, must-revalidate, pre-check=0, post-check=0, max-age=0\r\nPragma: no-cache\r\nContent-type: multipart/x-mixed-replace;boundary=www.briup.com\r\n\r\n";
	if(write(fd,reponse,strlen(reponse))!= strlen(reponse)){
		fprintf(stderr,"write:%s\n",strerror(errno));
		pthread_exit((void*)0);
	}
	while(1){
		memset(buffer,0,sizeof(buffer));
		sprintf(buffer,"--www.briup.com\nContent-type: image/jpeg\nContent-Length: %d\n\n",buf_size+DHT_SIZE);
		if(write(fd,buffer,strlen(buffer)) < 0){
			printf("客户端已关闭！\n");
			break;
		}
		pthread_mutex_lock(&mutex);
		print_picture(fd,frame_buf2,buf_size);
		pthread_mutex_unlock(&mutex);
		usleep(100000);
	}
	close(fd);
	return (void*)0;
}

int main(int argc,char *argv[]){
	if(argc<2){
		fprintf(stderr,"usage:%s\n",argv[1]);
		exit(1);
	}
	if(signal(SIGINT,signal_handler)==SIG_ERR){
		fprintf(stderr,"signal:%s\n",strerror(errno));
		exit(1);
	}
	if(signal(SIGPIPE,signal_handler)==SIG_ERR){
		fprintf(stderr,"signal:%s\n",strerror(errno));
		exit(1);
	}
	//socket
	socketfd=socket(AF_INET,SOCK_STREAM,0);	
	if(socketfd<0){
		fprintf(stderr,"socket:%s\n",strerror(errno));
		exit(1);
	}
	//设置IP
	struct sockaddr_in sockaddr;
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family=AF_INET;
	sockaddr.sin_port=htons(atoi(argv[1]));
	sockaddr.sin_addr.s_addr=INADDR_ANY;//127.0.0.1
	//char buf[16]={"172.16.0.45"};
	//inet_pton(AF_INET,buf,&(sockaddr.sin_addr.s_addr));
	//绑定IP
	if((bind(socketfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))<0)){
		fprintf(stderr,"bind:%s\n",strerror(errno));
		exit(1);
	}
	//监听
	if(listen(socketfd,3)<0){
		fprintf(stderr,"listen:%s\n",strerror(errno));
		exit(1);
	}
	//初始化摄像头
	cameraFd=open("/dev/video0",O_RDWR,0);//阻塞
	init_camera();
	//创建一个图片数据采集线程
	pthread_t pth;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	int ret;
	if((ret=pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED))!=0){
		fprintf(stderr,"pthread_setdetachstat:%s\n",strerror(ret));
		exit(1);
	}
		if((ret=pthread_create(&pth,&attr,th_fun2,NULL))!=0){
			fprintf(stderr,"pthread_create:%s\n",strerror(ret));
			exit(1);
		}
	//连接客户端
	while(1){
		struct sockaddr_in clientaddr;
		int len=sizeof(clientaddr);
		int fd=accept(socketfd,(struct sockaddr*)&clientaddr,&len);
		if(fd<0){
			fprintf(stderr,"accept:%s\n",strerror(errno));
			continue;
		}
		out_client(clientaddr);
		if((ret=pthread_create(&pth,&attr,th_fun1,(void*)fd))!=0){
			fprintf(stderr,"pthread_create:%s\n",strerror(ret));
			continue;
		}
	}
	return 0;
}
