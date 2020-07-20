# -*- coding: utf-8 -*-
import scrapy
import re
from MySpider2.items import Myspider2Item

class SpiderSpider(scrapy.Spider):
    name = 'spider'
    allowed_domains = ['bbs.pku.edu.cn']
    start_urls = ['https://bbs.pku.edu.cn/v2/thread.php?bid=690']

    def parse(self, response):
        #第一次处理start_urls，此时的response是服务器对该url，get/post请求的回复
        li_url=response.xpath("//div[@class='list-item-topic list-item']/a/@href").extract()#得到所有的url的列表
        #找出该page下的所有的发帖
        for li in li_url:
            url=response.urljoin(li)
            yield scrapy.Request(url,callback=self.parse2)
            #将该url（即为每个帖子的url）的response传递给parse2中，可在其中完成操作
        page_now=response.xpath("//div[@class='paging']/div[@class='paging-input-wrapper']/input/@value").extract_first()
        page_max=response.xpath("//div[@class='paging']/div[@class='paging-input-wrapper']/input/@max").extract_first()
        if int(page_now)<int(page_max):
        # if int(page_now) < 50:
            next=response.xpath("(//div[@class='paging']/div[@class='paging-button n'])[last()]/a/@href").extract_first()
            next_page = response.urljoin(next)
            yield scrapy.Request(next_page, callback=self.parse)
            #此处进行翻页操作


    def parse2(self,response):
        reply_list=response.xpath("//div[@class='card-list']/div[@class='post-card']")
        item = Myspider2Item()  # 使用构建函数构建item对象
        item['title'] = response.xpath("//header/h3/text()").extract_first()  # 返回列表的第一个字符串
        item_all=[]
        for reply in reply_list:
            id=reply.xpath("./div[@class='post-owner']/p/@title").extract_first()
            if id=='心理咨询师':
                #此处非常非常的关键！因为她有换行，存放在不同的p中，若是指定p[1]则有可能少取，若加上position，则可能多选，
                #经过研究发现，只要去除包含class='quotehead' or class='blockquote'的p，则可以取出完整数据
                item_some=reply.xpath("./div[@class='post-main']//div[@class='body file-read image-click-view']/p[not(@class='quotehead' or @class='blockquote')]/text()").extract()
                #此时是一个列表，每个元素是一行的回复
                item_all.extend(item_some)
        item['reply'] = " ".join(item_all)
        # 将几个元素合成一个字符串输出，中间用空格分割。
        yield item


        page_reply_now=response.xpath("//div[@class='paging paging-top']/div[@class='paging-input-wrapper']/input/@value").extract_first()
        # 当前页数
        page_reply_max=response.xpath("//div[@class='paging paging-top']/div[@class='paging-input-wrapper']/input/@max").extract_first()
        # 总页数
        if int(page_reply_now)<int(page_reply_max):
            next=response.xpath("(//div[@class='paging paging-top']/div[@class='paging-button n'])[last()]/a/@href").extract_first()
            next_reply_page = response.urljoin(next)
            yield scrapy.Request(next_reply_page, callback=self.parse2)
            # callback 重新调用自己，url为next_reply_page
            #此处进行帖子内部的翻页操作




