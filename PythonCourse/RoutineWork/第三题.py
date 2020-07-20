import math
x = eval(input())
print("单分支实现:")
if x%2!=0:
    print("{}".format(math.sqrt(x)))
if x%2==0:
    print("{:f}".format(math.pow(x, 1.0/3)))

print("双分支实现：")
if x%2!=0:
    print("{}".format(math.sqrt(x)))
else:
    print("{:f}".format(math.pow(x, 1.0/3)))