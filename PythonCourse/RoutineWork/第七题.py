d = dict()
for i in range(1,31):
    print('输入第{}个名字：'.format(int(i)))
    name = input()
    print('输入第{}个成绩：'.format(int(i)))
    score = eval(input())
    d.setdefault(name, score)
flag = 0
sum = 0.0
for v in d.values():
    sum += v
    if flag == 0:
        max=min=v
        flag = 1
    else :
        if(v > max):
            max=v
        if(v< min):
            min=v

print('最小值：{}\n最大值：{}\n平均分:{}'.format(min,max,sum/len(d)))

