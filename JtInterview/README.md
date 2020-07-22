# #8 老司机必备技能！！！让爬虫来解放你的双手

## 爬取图片，按cos角色分类

### 思路

- 将需要获取的url分为三个部分

  > 1. cos角色分类页面的url
  > 2. 某个特定角色的图片集合页面的url
  > 3. 单张图片的url

- 循序渐进，获取到图片的url，完成分类爬取

- 根据得到的url下载图片

### 尝试爬取

#### 尝试1

1. 从url_角色分类页获取响应，并从中提取HTML

```python
response = requests.get(url=url, headers=headers)
page_html = response.text
```

2. 得到url_特定角色

```python
soup = BeautifulSoup(page_html,'lxml')
data=soup.select('body #content .photo-list a')
href_content =item.get('href')   
link_number=re.findall(r'\d+',href_content)[0]
```

> 由于不同角色页的网页url只有一串数字不同，故从中提取出link_number，至此得到了每个角色的url

3. 得到特定角色网站的源码，并从中提取出每张图片的url

> 这一步无法完成，虽然这些url在浏览器的开发者工具中可以查看到，但是在使用bs4解析后得到的html源码会缺失这些图片的url，猜测可能是’lxml‘不稳定，随后尝试更改‘lxml’为‘html5lib’与‘html.parse'，仍旧失败。期间也使用过re.request和urllib库，都以失败告终。

![1569739889225](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121934.png)

#### 尝试2

1. 本次尝试基于尝试1的前两步进行
2. 基于Network-XHL中的文件进行爬取

> 经过网络搜索和观察，发现在特定角色网站中，打开开发者工具，在Network-XHL-Preview目录中的HTML文件内容中，有每张图片的url，在Network-XHL-Headers目录中存在该文件的url地址，且经过对比，只有两个属性是不同的：
>
> - 红框118
>
> 这个数字刚好是该特定角色的link_number[^尝试1.2]
>
> - 红框page=1
>
> 每个页面有数个page，每个page中存在多张图片

![1569737705192](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121945.png)

![1569737727599](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121951.png)

3. 通过分析单张图片网址的源代码，发现图片的url与第二步提取出来的url并不一样，经过比较，唯一的不同之处便是最后的图片大小：

> - 正常下载的高清版本url：xxx-3000.jpg
> - 目前提取出的url：xxx-350×600.jpg

4. 最终决定处理方案：

> - 使用正则表达式提取url，去除末尾的-350×600.jpg，再加上-3000.jpg
>
> ```python
> images_url_headt=re.findall(r'"sq150_url":"(.*?)-', page_html)[0]
> image_url=images_url_head+'-3000.jpg'
> ```

5. 解决了图片url，最后还有三个问题

> - 文件名的获取
>
> ```python
> title_try=re.findall(r'.+',item.get_text())[0]    #初步得到cos角色名
> title=re.sub('[^a-zA-Z ]','',title_try)           #经测试发现，存在"Menma"和"/"两个文件名，由于存在"和/无法创建文件夹，故用re.sub删去
> ```
>
> - 文件存储在哪，如何创建文件夹
>
> ```python
>  if not os.path.exists('images'):
>      os.mkdir('images')                         #创建主文件夹
>  if not os.path.exists('images\\%s'%title):
>      os.mkdir('images\\%s'%title)               #创建每个cos角色的文件夹
> ```
>
> - 如何确定page数量
>
> > 在Network-XHL-Preview目录中的HTML文件内容中，除了图片url，还有一个内容：next_page
> >
> > 若是该页为终止页，则next_page则为null，否则则依次为1、2、3、...
>
> ```python
> next_page.isdigit()                                #利用正则表达式获取next_page，利用isdigit()方法判断是否是纯数字，若为null，则为最终页
> ```
>
> - 如何完成图片的下载
>
> ```python
> image_data = requests.get(url=image_url, headers=headers).content
> with open(image_path+image_name, 'wb') as fp:
>      fp.write(image_data)
> ```

### 爬取结果

![](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722121959.png)

![1569739454072](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722122020.png)

![1569739479290](https://github.com/HappyTsing/Figure-bed/raw/master/img/20200710152815.png)

### 完整代码和注释

```python
import requests
from bs4 import BeautifulSoup
import re
import os
def download_image(image_url,image_path,image_name):   #运行一次，下载完一张图片
    print('download %s%s'%(image_path,image_name)) #显示打印进度
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36'
    }
    print(image_url)
    image_data = requests.get(url=image_url, headers=headers).content
    with open(image_path+image_name, 'wb') as fp:
        fp.write(image_data)

def get_cos_images_page(link_number,image_path,page): #运行一次，下载完一个page的照片
    # link_number:每个cos角色链接唯一不同的数字，故一个link_number代表一个角色
    # image_path:照片的下载文件夹
    # page:每一个cos角色有2-3个page，每个page里装有一定的图片
    # number:图片编号
    number=1#每个文件夹中图片从1开始命名
    print('page={}'.format(page))
    url = 'https://worldcosplay.net/api/member/126641/characters/%s/photos.json?limit=16&p3_photo_list=true&page=%d'%(link_number,page)
    #该cos角色的总览页的url
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36'
    }
    #用于模拟浏览器发送get请求
    response = requests.get(url=url, headers=headers)
    #服务器收到请求后的回应
    page_html = response.text   #获得该page的html
    images_url = re.findall(r'"sq150_url":"(.*?)-', page_html)
    #加上()后，"sq150_url":"和-不显示，去掉()会显示，这两个单词中间的内容刚好就是"http...(-xx.jpg)"去除（-xx.jpa）
    #因为，高清大图是（-3000.jpg），而链接中是（350x600.jpg），而前面的内容相同，故而先去前面的，在＋上'350x600.jpg'
    next_page=re.findall(r'"next_page":(.*?)}',page_html)[0]
    #若next_page==null,则无下一页。
    for image_url_header in images_url:
        image_url=image_url_header+'-3000.jpg'
        #images_url是一个列表，其中有许多image_url,循环调用该page下所有的image_url，每个image_url对应一张图片的地址
        image_name='%d.%d.jpg'%(page,number)   #为图片命名(page.number)
        download_image(image_url,image_path,image_name)  #调用下载函数，下载该image_url的图片
        number+=1
    # 若next_page不等于null，则page=page+1
    return next_page

def get_cos_images(link_number,image_path):  #运行一次，下载完一个cos角色的所有page的所有图片
    page=1
    next_page='0'
    #计算page，调用get_cos_images_page
    while(next_page.isdigit()):  #判断是否是纯数字，若为null，则退出循环
        next_page=get_cos_images_page(link_number, image_path, page)
        page+=1;

        
url = 'https://worldcosplay.net/member/Itsuki-chan/characters'
headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36'
    }
response = requests.get(url=url, headers=headers)#模拟浏览器发送请求
page_html = response.text
soup = BeautifulSoup(page_html,'lxml')
data=soup.select('body #content .photo-list a')   #标签不变，id加#，类名加.得到固定区域的HTML数据
for item in data: #遍历data，在对应角色得网站里，爬取图片，下载，再循环下一个角色，循环完成则完成目标。
    href_content =item.get('href')        #得到链接
    link_number=re.findall(r'\d+',href_content)[0]
    print(link_number)    #显示打印的cos角色的url中的特有数字
    title_try=re.findall(r'.+',item.get_text())[0] #初步得到cos角色名
    title=re.sub('[^a-zA-Z ]','',title_try)        #经测试发现，存在"Menma"和"/"两个文件名，由于存在"和/无法创建文件夹，故用re.sub删去
    print(title)                                   #打印文件名，即下载的cos角色名
    if not os.path.exists('images'):
        os.mkdir('images')                         #创建主文件夹
    if not os.path.exists('images\\%s'%title):
        os.mkdir('images\\%s'%title)    #创建每个cos角色的文件夹
    image_path='images\\%s\\'%title     #最后的"\\"是为了给图片名留下位置，此处写了在函数download_image中不用写，直接加上"图片名"即可
    get_cos_images(link_number,image_path)  #传递函数参数，获得所有照片。

```


## 爬取信软官方，使用scrapy，保存数据至数据库

### 思路

1. 在items中完成item对象的设定,并在spider.py中导入,使用其构造器完成item对象的构造在spider.py中设置url和item的获取,通过yield传递给pipelines.py
2. 在spider.py中设置url和item的获取,通过yield传递给pipelines.py
3. 构建数据库，此处使用MySQL数据库
4. 在pipelines.py中完成上传至数据库的操作
5. 构建两个spider.py,分别命名为student.py和academic.py,为每个spider.py构建自己的pipeline完成上传至数据库的两个table中的操作
6. 在settings.py中进行设置,使爬虫能正常运行

### 构建MySQL数据库

1. 登陆

```mysql
mysql -u root -p
```

![1570330040816](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722122030.png)

2. 查看已有数据库，并构建一个名为test1的数据库

```mysql
show databases；
CREATE DATABASE test1；
```

![1570330166168](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722122036.png)

3. 在test1中创建两个table，分别取名为student和academic，用于存放爬取的学生科和教务科的数据，具有三个属性，time存储时间，title存储内容，id表示标号，属于key、auto_increment

```mysql
use test1;
show tabel;
CREATE TABLE student (time INT(15) NOT NULL,title VARCHAR(255) NOT NULL,id INT(4) NOT NULL AUTO_INCREMENT KEY);
CREATE TABLE academinc (time INT(15) NOT NULL,title VARCHAR(255) NOT NULL,id INT(4) NOT NULL AUTO_INCREMENT KEY);
```

![1570331008983](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722122044.png)

### 尝试爬取

1. items.py

```python
import scrapy
class MyspiderItem(scrapy.Item):
    # define the fields for your item here like:
    title= scrapy.Field()
    time=scrapy.Field()
    pass
```

2. item的构造

> xpath到相应位置，取出所需内容至item，并将其传递给pipelines.py

```python
li_list =response.xpath("//div[@class='container']//ul[@class='new-list clearfix']/li/a")
      for li in li_list:
          item=MyspiderItem()
          item['title']=li.xpath("./@title").extract_first()
          item['time']=li.xpath("./span[@class='new-time']/text()").extract_first()
          yield item
```

3. 完成翻页操作

> 通过对网页中“下一页”按钮的检查，发现它出现在li的最后一列，故而在xpath索引时，使用/li[last()]

```python
next_page = response.xpath(         "//div[@class='container']//ul[@class='paginationitem']/li[last()]/a/@href").extract_first()
```

4. 实现爬取200条

> 由于每一页有二十条内容，故而爬取十页即可实现,通过callback，使之完成反复调用自身的操作

```python
num = int(re.findall("page=(.+)",next_page)[0])
if num<=10: #若next_page不存在，则表示已经到达最后一页
        next_url = response.urljoin(next_page)
        yield scrapy.Request(next_url,callback=self.parse)
```

5. 在pipelines中实现链接、上传

```python
class MyspiderPipeline_stu(object):
    def __init__(self):
        self.connect= pymysql.connect(host="localhost", user="root", password="081008", database='test', charset='utf8')
        self.cursor = self.connect.cursor()
    def process_item(self, item,spider):
        self.cursor.execute('INSERT INTO stu (time,title) VALUES("{}","{}")'.format(item['time'],item['title']))
        self.connect.commit()
        return item
    def close_spider(self,spider):
        self.cursor.close()
        self.connect.close()

class MyspiderPipeline_aca(object):
    def __init__(self):
        self.connect= pymysql.connect(host="localhost", user="root", password="081008", database='test', charset='utf8')
        self.cursor = self.connect.cursor()
    def process_item(self, item,spider):
        self.cursor.execute('INSERT INTO aca (time,title) VALUES("{}","{}")'.format(item['time'],item['title']))
        self.connect.commit()
        return item
    def close_spider(self,spider):
        self.cursor.close()
        self.connect.close()

```

6. 为每个spider配置pipeline

```python
custom_settings = {
    'ITEM_PIPELINES':{'MySpider.pipelines.MyspiderPipeline_aca': 301,}
    }
```

### 爬取结果

![1570338423791](https://github.com/WlqFigureBed/FigureBed-one/raw/master/img/20200722122055.png)
