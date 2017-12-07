#!/bin/bash

NGINX_VERSION='1.9.4'

docker run --name=test-proxy \
    -v /opt/nginx/conf:/etc/nginx/ \
    -v /opt/static:/opt/static \
    -v /opt/nginx/test:/opt/nginx/test \
    -p 80:80 \
    -p 443:443 \
    -p 8000:8000 \
    -d nginx:$NGINX_VERSION
