import os
from django.utils import timezone

def Error_info(filepath, line, error):
    now_date = timezone.now().strftime("%Y-%m-%d %H:%M:%S")
    log_path = '%s/log' % os.path.dirname(__file__) 

    if not os.path.exists(log_path):
        os.mkdir(log_path)

    fp = open('%s/error.log' % log_path,'a')
    fp.writelines('%s, file %s, line %s, error %s\n' % (now_date, filepath, line, error))
    fp.close()
    
