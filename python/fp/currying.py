#
# The technique of transforming a function that takes multiple arguments
# in such a way that it can be called as a chain of functions each with a 
# single argument 
#
import functools
import operator
def foo(a,b,c):
    return a+b+c

foo2 = functools.partial(foo,b = 2 )
print foo2(a=1, c=3)

##################################################

def fsum(f):
    def apply(a,b):
        return sum(map(f,range(a,b+1)))
    return apply

print fsum(lambda x:x*2)(1,10)

print fsum(functools.partial(operator.mul,2))(1,10)

###########################
ss = ["UA","PyCon","2012"]
#BAD
print reduce(lambda acc,s:acc+len(s),ss ,0)
#NOT BAD
print reduce(lambda l,r:l+r, map(lambda s:len(s), ss))
#GOOD
print reduce(operator.add,map(len,ss))


