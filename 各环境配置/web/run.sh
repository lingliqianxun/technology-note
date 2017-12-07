#!/bin/bash

set -e

if [ "`ls -A /var/log/tomcat6`" = "" ];then
    #修改运行用户
    #(原TOMCAT6_USER=tomcat6,TOMCAT6_GROUP=tomcat6)
    sed -i "s/TOMCAT6_USER=tomcat6/TOMCAT6_USER=www-data/g" /etc/default/tomcat6
    sed -i "s/TOMCAT6_GROUP=tomcat6/TOMCAT6_GROUP=www-data/g" /etc/default/tomcat6
    #添加用户组
    #(原:/usr/sbin/nologin)
    usermod -s /bin/bash www-data
    usermod -a -G tomcat6 www-data
    #创建文件夹
    mkdir -p /usr/share/tomcat6/server/classes
    mkdir -p /usr/share/tomcat6/shared/classes
    #修改文件权限
    #(原:drwxr-xr-- tomcat6 adm)
    rmdir /var/log/tomcat6
    mkdir -m 770 /var/log/tomcat6
    chown tomcat6. /var/log/tomcat6
    #(原:drwxr-x--- tomcat6 adm)
    rmdir /var/cache/tomcat6
    mkdir -m 770 /var/cache/tomcat6
    chown tomcat6. /var/cache/tomcat6
    #修改时区
    echo "Asia/Shanghai" > /etc/timezone
    cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
else
    #重启后删除原项目
    rm -rf /var/lib/tomcat6/webapps/*
fi

#用户www-data启动tomcat6
cp /opt/webapps/juyaooms.war /var/lib/tomcat6/webapps/
su www-data -c /usr/share/tomcat6/bin/startup.sh
tail -f /var/lib/tomcat6/logs/catalina.out

