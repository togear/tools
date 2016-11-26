#!/usr/bin/python

#1) 代码更简单了。
#2）数据集，操作，返回值都放到了一起。
#3）你在读代码的时候，没有了循环体，于是就可以少了些临时变量，以及变量倒来倒去逻辑。
#4）你的代码变成了在描述你要干什么，而不是怎么去干。

num =[2, -5, 9, 7, -2, 5, 3, 1, 0, -3, 8]
positive_num = filter(lambda x: x> 0, num)
average = reduce(lambda x,y: x+y, positive_num) / len( positive_num )
print average
