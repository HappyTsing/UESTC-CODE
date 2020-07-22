- 基于scrapy框架实现爬虫

![image-20200710135453357](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121743.png)

- items.py：构建存储的字典结构
- pipelines.py：实现与数据库相连接，并将爬取的数据传送给数据库，此处为MySQL

![1570410193554](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121748.png)

- spider.py：实现url定位、翻页、爬取内容保存至item，再yield给pipelines.py

# 爬虫项目工作机制

### 浏览器的工作原理

![1570411251228](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121752.png)

### 爬虫工作机制

> 爬虫的原理即位模仿浏览器的工作原理直接实现数据的爬取

![1570412399038](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121759.png)

### 构建MySQL数据库

1. 登陆

```mysql
mysql -u root -p
```

![1570330040816](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121828.png)

2. 查看已有数据库，并构建一个名为test1的数据库

```mysql
show databases；
CREATE DATABASE test1；
```

![1570330166168](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121807.png)

3. 在test1中创建1个table，分别取名为spider，用于存放爬取的学生科和教务科的数据，具有三个属性，title存储标题，reply存储内容

```mysql
use test1;
show tabel;
CREATE TABLE spider (reply text NULL,title VARCHAR(255) NOT NULL);
```

![1570412843511](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121813.png)

### 基于scrapy实现爬虫

#### 思路

1. 在items中完成item对象的设定,并在spider.py中导入,使用其构造器完成item对象的构造在spider.py中设置url和item的获取,通过yield传递给pipelines.py
2. 构建数据库，此处使用MySQL数据库
3. 构建spider.py,完成实现url定位、翻页、爬取内容保存至item，再yield给pipelines.py
4. 在pipelines.py中完成上传至数据库的操作
5. 在settings.py中进行设置,使爬虫能正常运行

#### 爬取过程解释

1. item对象的设定

```python
import scrapy
class Myspider2Item(scrapy.Item):
    title = scrapy.Field()
    reply=scrapy.Field()
    pass
```

2. spider.py的实现

> 问题有三：
>
> 如何实现翻页：在帖子总览的翻页（共200+页），在帖子内部的翻页（1~n页）
>
> 如何提取心理咨询师的回答
>
> 如何保存数据
>
> 函数有二：
>
> parse：进行帖子总览翻页，并调用parse2完成内容爬取
>
> parse2：完成内容爬取工作，并在帖子内部翻页，保证数据完整

- 翻页：两个翻页的实现方法相同，通过定位找到总页数和当前页数，若是当前页数小于总页数，则定位到下一页的url，翻页。

```python
        page_now=response.xpath("//div[@class='paging']/div[@class='paging-input-wrapper']/input/@value").extract_first()
        page_max=response.xpath("//div[@class='paging']/div[@class='paging-input-wrapper']/input/@max").extract_first()
        if int(page_now)<int(page_max):
            next=response.xpath("(//div[@class='paging']/div[@class='paging-button n'])[last()]/a/@href").extract_first()
            next_page = response.urljoin(next)
            yield scrapy.Request(next_page, callback=self.parse)
            #进行帖子总览的翻页操作

            
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
```

- 提取心理咨询师的回答

```python
    def parse2(self,response):
        reply_list=response.xpath("//div[@class='card-list']/div[@class='post-card']")
        item = Myspider2Item()  # 使用构建函数构建item对象
        item['title'] = response.xpath("//header/h3/text()").extract_first()  # 返回列表的第一个字符串，此处获得帖子标题
        item_all=[]  #构建列表，存储心理咨询师在该帖子下的所有回答
        for reply in reply_list:
            id=reply.xpath("./div[@class='post-owner']/p/@title").extract_first()
            if id=='心理咨询师':
                #此处非常非常的关键！因为她有换行，存放在不同的p中，若是指定p[1]则有可能少取，若加上position，则可能多选，出现非相关信息，最后经过研究发现，只要去除包含class='quotehead' or class='blockquote'的<p>，即可取出完整数据
                item_some=reply.xpath("./div[@class='post-main']//div[@class='body file-read image-click-view']/p[not(@class='quotehead' or @class='blockquote')]/text()").extract()
                #此时是一个列表，每个元素是一行的回复
                item_all.extend(item_some)
                #将该页下心理咨询师的回答添加到列表中
                
        item['reply'] = " ".join(item_all)
        # 将列表中的所有回答合成一个字符串输出，中间用空格分割。
        yield item
        #传递item给pipeline完成后续上传数据库操作
```

- 两个函数的联结使用

```python
 def parse(self, response):
        #第一次处理start_urls，此时的response是服务器对该url，get/post请求的回复
        #后续每次处理的url都是其翻页后的url
        li_url=response.xpath("//div[@class='list-item-topic list-item']/a/@href").extract()#得到所有的url的列表
        #找出该page下的所有的发帖
        for li in li_url:
            url=response.urljoin(li)
            yield scrapy.Request(url,callback=self.parse2)
            #将该url（即为每个帖子的url）的response传递给parse2中，可在其中完成操作
```

- 数据上传到数据库，实现保存

```python
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
```
