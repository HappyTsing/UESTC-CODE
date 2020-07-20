n = eval(input("输入n:"))
sum = 0.0
for i in range(1, n+1):
    sum += 1/(4*int(i)-3) - 1/(4*int(i)-1)
print("pi={}".format(4*sum))
