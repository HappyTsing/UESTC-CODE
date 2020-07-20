# -*- coding: utf-8 -*-
import scrapy
from SpiderUestc.items import MyspiderItem
import re
class studentSpider(scrapy.Spider):
    name = 'student'                   #爬虫名字
    allowed_domains = ['www.ss.uestc.edu.cn']   #允许爬取的范围
    start_urls = ['http://www.ss.uestc.edu.cn/noticesList.do?type=90']#最开始请求的url地址
    custom_settings = {
    'ITEM_PIPELINES':{'SpiderUestc.pipelines.MyspiderPipeline_stu': 300,}

    }
    def parse(self, response):
        #处理start_urls地址对应的响应
        #获取这一page中的所有的信息，形成一个列表
        li_list =response.xpath("//div[@class='container']//ul[@class='new-list clearfix']/li/a")
        #从列表中去除一个，将其传给字典，字典yield给pipelines.py，在pipelines中完成下载工作
        for li in li_list:
            item=MyspiderItem()
            item['title']=li.xpath("./@title").extract_first()
            item['time']=li.xpath("./span[@class='new-time']/text()").extract_first()
            yield item
        #完成翻页的操作
        next_page = response.xpath(
            "//div[@class='container']//ul[@class='pagination-item']/li[last()]/a/@href").extract_first()
        num = int(re.findall("page=(.+)",next_page)[0])
        if num<=10: #若next_page不存在，则表示已经到达最后一页
            next_url = response.urljoin(next_page)
            yield scrapy.Request(next_url,callback=self.parse)


