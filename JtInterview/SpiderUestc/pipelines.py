# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html

import pymysql

# def save_database():
#     conn = pymysql.connect(host="localhost", user="root", password="081008", database='test', charset='utf8')
#     cursor = conn.cursor()
#     # NOT NULL UNIQUE 表示唯一不重复
#     # NOT NULL 表示不接受空值
#     sql = """
#     CREATE TABLE USER1(id INT auto_increment PRIMARY KEY,
#     title VARCHAR NOT NULL UNIQUE,
#     time CHAR(12) NOT NULL ）
#     ENGINE=innodb DEFAULT CHARSET=utf8;
#     """
#     # 构建需要执行的sql语句
#     sql = ""
#
#     # 执行SQL语句
#     cursor.execute(sql)
#     #提交事务
#     conn.commit()
#     # 关闭光标对象
#     cursor.close()
#     # 关闭数据库连接
#     conn.close()



class MyspiderPipeline_stu(object):
    def __init__(self):
        self.connect= pymysql.connect(host="localhost", user="root", password="081008", database='test1', charset='utf8')
        self.cursor = self.connect.cursor()
    def process_item(self, item,spider):
        self.cursor.execute('INSERT INTO student (time,title) VALUES("{}","{}")'.format(item['time'],item['title']))
        self.connect.commit()
        return item
    def close_spider(self,spider):
        self.cursor.close()
        self.connect.close()

class MyspiderPipeline_aca(object):
    def __init__(self):
        self.connect= pymysql.connect(host="localhost", user="root", password="081008", database='test1', charset='utf8')
        self.cursor = self.connect.cursor()
    def process_item(self, item,spider):
        self.cursor.execute('INSERT INTO academic (time,title) VALUES("{}","{}")'.format(item['time'],item['title']))
        self.connect.commit()
        return item
    def close_spider(self,spider):
        self.cursor.close()
        self.connect.close()
