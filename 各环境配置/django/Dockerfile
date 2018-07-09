FROM ubuntu

#更新资源
RUN apt-get update
#安装apache
RUN apt-get -y install apache2
#安装apache与项目中间件(需官网源)
RUN apt-get -y install libapache2-mod-wsgi
RUN apt-get -y install libapache2-mod-wsgi-py3
#安装django需求
RUN apt-get -y install python-dev
RUN apt-get -y install python3-dev
RUN apt-get -y install postgresql-server-dev-9.3 

#修改默认为python3环境
RUN cp /usr/bin/python3 /usr/bin/python
#安装项目需求
RUN apt-get -y install python3-pip
RUN pip3 install Django 
RUN pip3 install django-filter 
RUN pip3 install djangorestframework 
RUN pip3 install setuptools 
RUN pip3 install Pillow 
RUN pip3 install python3-memcached 
RUN pip3 install psycopg2 
RUN pip3 install pycrypto 
#10.1.1.8镜像
#RUN pip3 install Django -i http://10.1.1.8/pip/simple/
#RUN pip3 install django-filter -i http://10.1.1.8/pip/simple/
#RUN pip3 install djangorestframework -i http://10.1.1.8/pip/simple/
#RUN pip3 install setuptools -i http://10.1.1.8/pip/simple/
#RUN pip3 install Pillow -i http://10.1.1.8/pip/simple/
#RUN pip3 install python3-memcached -i http://10.1.1.8/pip/simple/
#RUN pip3 install psycopg2 -i http://10.1.1.8/pip/simple/
#RUN pip3 install pycrypto -i http://10.1.1.8/pip/simple/
#阿里云镜像-i http://mirrors.aliyun.com/pypi/simple/ --trusted-host mirrors.aliyun.com

#安装语言包
RUN apt-get install -y locales
RUN /usr/share/locales/install-language-pack en_US.UTF-8 
ENV LANG en_US.UTF-8 
ENV LANGUAGE en_US.UTF-8 
ENV LC_ALL en_US.UTF-8 

#添加项目代码
ADD . /project/hive
#添加虚拟主机端口6789
ADD ./hive-default.conf /etc/apache2/sites-available/
RUN a2ensite hive-default.conf

#设置共享文件
VOLUME ["/opt/static"]
#开放端口
EXPOSE 6789 
ENTRYPOINT service apache2 start && tail -f /var/log/apache2/error.log 
#CMD service apache2 start && /bin/bash 
