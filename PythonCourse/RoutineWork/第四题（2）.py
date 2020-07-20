import math
i = 1
sum = 0.0
while math.fabs(1/(4*int(i)-3) - 1/(4*int(i)-1)) >= 1e-6:
    sum += 1 / (4 * int(i) - 3) - 1 / (4 * int(i) - 1)
    i += 1
print("pi={}".format(4*sum))
