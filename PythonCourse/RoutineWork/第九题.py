from math import sqrt


class POINT:
    def __init__(self, m1, n1, z1, m2, n2, z2):
        self.x1 = m1
        self.y1 = n1
        self.z1 = z1
        self.x2 = m2
        self.y2 = n2
        self.z2 = z2

    def direction_cosine(self):
        cosx = (self.x1 - self.x2) / sqrt((self.x1 - self.x2) ** 2 + (self.y1 - self.y2) ** 2 + (self.z1 - self.z2) ** 2)
        cosy = (self.y1 - self.y2) / sqrt((self.x1 - self.x2) ** 2 + (self.y1 - self.y2) ** 2 + (self.z1 - self.z2) ** 2)
        cosz = (self.z1 - self.z2) / sqrt((self.x1 - self.x2) ** 2 + (self.y1 - self.y2) ** 2 + (self.z1 - self.z2) ** 2)
        print("({},{},{})".format(cosx, cosy, cosz))

    def distance(self):
        dis = sqrt((self.x1 - self.x2) ** 2 + (self.y1 - self.y2) ** 2 + (self.z1 - self.z2) ** 2)
        print("距离：{}".format(dis))


a = POINT(1, 1, 1, 0, 0, 0)
a.direction_cosine()
a.distance()