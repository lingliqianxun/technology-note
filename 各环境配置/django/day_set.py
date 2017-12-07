#!/home/username/test/bin/python
import os,sys

BASE_DIR = '/home/username/test/'

#添加项目路径到环境变量
sys.path.append(BASE_DIR)
#切换工作路径
os.chdir(os.path.dirname(__file__))

#通过 wsgi 连接
import test.wsgi

#处理
from django.utils import timezone
