FROM ubuntu

#配置Apt Repository
RUN echo "deb http://apt.postgresql.org/pub/repos/apt/ trusty-pgdg main" >> /etc/apt/sources.list.d/pgdg.list
RUN apt-get install -y software-properties-common
RUN apt-get install -y wget
RUN wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
#更新资源
RUN apt-get update
#安装postgresql
RUN apt-get install -y postgresql 
RUN apt-get install -y postgresql-server-dev-9.4
#安装语言包
RUN apt-get install -y locales
RUN /usr/share/locales/install-language-pack en_US.UTF-8 
RUN /usr/share/locales/install-language-pack zh_CN.UTF-8 
ENV LANG en_US.UTF-8 
ENV LANGUAGE en_US.UTF-8 
ENV LC_ALL en_US.UTF-8 
#配置postgresql
RUN echo "local    all    root                    trust" >> /etc/postgresql/9.4/main/pg_hba.conf
RUN echo "host     all    all        0.0.0.0/0    md5"   >> /etc/postgresql/9.4/main/pg_hba.conf
RUN echo "listen_addresses='*'" >> /etc/postgresql/9.4/main/postgresql.conf
#创建用户
USER postgres
RUN service postgresql start && \
psql -c "create user root with superuser password '123456';" && \ 
psql -c "create database root;"
USER root 
#修改时区
RUN echo "Asia/Shanghai" > /etc/timezone
RUN cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
#数据定时备份
RUN chmod 600 /var/spool/cron/crontabs/root
#共享文件
VOLUME  ["/opt"]
#开放端口
EXPOSE 5432 
#CMD service postgresql start && sleep 60 && psql < /opt/hive.sql && cron && /bin/bash 
CMD service postgresql start && cron && /bin/bash 
