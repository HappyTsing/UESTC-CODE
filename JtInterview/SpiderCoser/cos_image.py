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
        # 'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/77.0.3865.90 Safari/537.36'
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.89 Safari/537.36'

    }
# session =requests.Session()
# session.trust_env=False   #设置不使用代理！
response = requests.get(url=url, headers=headers)#模拟浏览器发送请求

page_html = response.text
soup = BeautifulSoup(page_html,'lxml')
data=soup.select('body #content .photo-list a')   #标签不变，id加#，类名加.得到固定区域的HTML数据
for item in data: #遍历data，在对应角色得网站里，爬取图片，下载，再循环下一个角色。
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
