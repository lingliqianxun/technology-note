#!/bin/bash


docker run --name=web-test \
    -v /opt/static/:/opt/static/ \
    -v /opt/webapps/:/usr/local/tomcat/webapps/ \
    -p 9876:8080 \
    -d test/web 
