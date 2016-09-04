#!/usr/bin/python
# -*- coding: UTF-8 -*

from time import time;
def speak(topic):
    print "My speach is "+topic

def timer(fn):
    def inner(*args, **kwargs):
        t = time()
        fn(*args,**kwargs)
        print "took {time}".format(time=time()-t)

    return inner

speaker = timer(speak)
speaker("FP with Python")
