string = input('输入字母标识符：')
s = string.lower()
sum = 0
for i in s:
    sum += ord(i)-96
print("{}".format(sum))
