FROM ubuntu

#更新资源
RUN apt-get update
#安装jdk
#RUN apt-get -y install default-jdk 
#安装apache
RUN apt-get -y install tomcat6 
#安装语言包
RUN apt-get install -y locales
RUN /usr/share/locales/install-language-pack en_US.UTF-8 
ENV LANG en_US.UTF-8 
ENV LANGUAGE en_US.UTF-8 
ENV LC_ALL en_US.UTF-8 
#设置环境变量
ENV CATALINA_HOME /usr/share/tomcat6
ENV CATALINA_BASE /var/lib/tomcat6
#ENV CATALINA_PID /var/run/tomcat6.pid
#ENV CATALINA_SH /usr/share/tomcat6/bin/catalina.sh
ENV CATALINA_TMPDIR /tmp/tomcat6-tomcat6-tmp 
RUN mkdir -p $CATALINA_TMPDIR
#添加初始运行文件
ADD ./run.sh /
#添加项目文件
#ADD ./juyaooms /var/lib/tomcat6/webapps/juyaooms
#设置共享文件
VOLUME ["/opt"]
#开放端口
EXPOSE 8080
#CMD /run.sh && su www-data -c /usr/share/tomcat6/bin/startup.sh && /bin/bash 
#ENTRYPOINT /run.sh && su www-data -c /usr/share/tomcat6/bin/startup.sh && tail -f /var/lib/tomcat6/logs/catalina.out 
CMD /run.sh  
