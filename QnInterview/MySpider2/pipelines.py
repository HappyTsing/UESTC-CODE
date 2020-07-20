# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://doc.scrapy.org/en/latest/topics/item-pipeline.html

#链接数据库，并将爬取到的内容上传
#注意，此处需要确保数据库已经被创建
import pymysql
class Myspider2Pipeline(object):
    def __init__(self):
        self.connect= pymysql.connect(host="localhost", user="root", password="081008", database='test', charset='utf8mb4')
        self.cursor = self.connect.cursor()
    def process_item(self, item,spider):
        if self.cursor.execute('INSERT INTO spider (title,reply) VALUES("{}","{}")'.format(item['title'],item['reply'])):
            print('上传成功')
        self.connect.commit()
        return item
    def close_spider(self,spider):
        self.cursor.close()
        self.connect.close()
