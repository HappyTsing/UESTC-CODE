import random
A=set()
for i in range(10):
    A.add(random.randint(0, 10))
B=set()
for j in range(10):
    B.add(random.randint(0, 10))
print(A,"A的长度：{} A的最大值：{} A的最小值：{}".format(len(A),max(A),min(A)))
print(B,"B的长度：{} B的最大值：{} B的最小值：{}".format(len(B),max(B),min(B)))
print("并集：",A.union(B))
print("交集：",A.intersection(B))
print("差集：",A.difference(B))