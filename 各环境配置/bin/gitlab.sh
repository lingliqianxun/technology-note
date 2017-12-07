#!/bin/bash

docker run --name=gitlab -d --link redis:redisio \
    -e 'GITLAB_HOST=10.1.1.1' \
    -e 'DB_TYPE=postgres' \
    -e 'DB_HOST=10.1.1.1' \
    -e 'DB_NAME=gitlab' \
    -e 'DB_USER=username' \
    -e 'DB_PASS=password' \
    -e 'GITLAB_PORT=10080' \
    -e 'GITLAB_SSH_PORT=10022' \
    -e 'GITLAB_SECRETS_DB_KEY_BASE=h4xWbn3czKKdvmVkzzVxkz3pbwNq3grH4FnCMFVmqr3xT99f4N3xHk7WmJLMVKbL' \
    -p 10022:22 -p 10080:80 \
    -v /opt/gitlab/data:/home/git/data \
    -v /var/run/docker.sock:/run/docker.sock \
    sameersbn/gitlab:8.4.4
