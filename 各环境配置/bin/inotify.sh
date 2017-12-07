#!/bin/bash

srcdir=/home/username/test/

/usr/bin/inotifywait -mrq --timefmt '%d/%m/%y %H:%M' --format '%T %w%f%e' -e close_write,modify,delete,create,attrib,move $srcdir |  while read file
do
rsync -vzrtopg $srcdir --delete test@10.1.1.8::ftp  --password-file=/home/test/passwd.txt
echo "  ${file} was rsynced" >> /tmp/rsync.log 2>&1
done
