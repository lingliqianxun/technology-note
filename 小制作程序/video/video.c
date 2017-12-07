#include<stdio.h>
#include<fcntl.h>
#include<errno.h>
#include<stdlib.h>
#include<linux/videodev2.h>
#include<sys/ioctl.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include"print.h"

int main(){
	//打开视频设备
	int cameraFd=open("/dev/video0",O_RDWR,0);//阻塞
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
	struct v4l2_requestbuffers req;
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
	typedef struct VideoBuffer{
		void *start;
		size_t length;
	}VideoBuffer;
	VideoBuffer *buffers=(VideoBuffer*)calloc(req.count,sizeof(*buffers));
	struct v4l2_buffer buf;
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
	//处理采集数据
	while(1){
		memset(&buf,0,sizeof(buf));
		buf.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;//数据流类型
		buf.memory=V4L2_MEMORY_MMAP;//视频采集方式
		buf.index=0;
		//读取缓存
		if(ioctl(cameraFd,VIDIOC_DQBUF,&buf)==-1){
			fprintf(stderr,"ioctl VIDIOC_DQBUF:%s\n",strerror(errno));
			exit(1);
		}
		//视频处理算法
		int fd=open("a.jpg",O_RDWR|O_CREAT|O_TRUNC,0664);
		if(fd<0){
			fprintf(stderr,"open:%s\n",strerror(errno));
			exit(1);
		}
		//格式转换
		//printf("buf.length: %d\n", buf.length);
		unsigned char *tmp=(char*)malloc(buf.bytesused);
		memset(tmp,0,buf.bytesused);
		yuv_to_jpeg((unsigned char*)buffers[buf.index].start,tmp,buf.bytesused,100);
		//打印
		print_picture(fd,tmp,buf.bytesused);
		free(tmp);
		close(fd);
		//重新放入缓存队列
		if(ioctl(cameraFd,VIDIOC_QBUF,&buf)==-1){
			fprintf(stderr,"ioctl VIDIOC_QBUF:%s\n",strerror(errno));
			exit(1);
		}
		usleep(300000);
	}
	//关闭视频显示
	if(ioctl(cameraFd,VIDIOC_STREAMOFF,&type)==-1){
		fprintf(stderr,"ioctl VIDIOC_STREAMON:%s\n",strerror(errno));
		exit(1);
	}
	close(cameraFd);
	return 0;
}
