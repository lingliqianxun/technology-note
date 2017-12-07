#!/bin/bash

srcdir_static=/opt/static/
srcdir_test=/opt/test/

/usr/bin/inotifywait -mrq --timefmt '%Y/%m/%d/ %H:%M:%S' --format '%T %w%f %e' -e close_write,modify,delete,create,attrib,move $srcdir_static $srcdir_test |  while read file
do
rsync -qzrtopg $srcdir_static --delete wo24-004::static
rsync -qzrtopg $srcdir_test--delete wo24-004::test
echo "${file} was rsynced" >> /var/log/inotifywait.log 2>&1
done
