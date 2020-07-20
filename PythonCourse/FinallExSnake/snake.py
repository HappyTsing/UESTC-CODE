import random
import pygame
import sys

from pygame.locals import *
snake_speed =15
windows_width = 800
windows_height = 600
cell_size = 20  #贪吃蛇身体方块大小

map_width=int(windows_width/cell_size)
map_height=int(windows_height/cell_size)

#定义颜色
white=(255,255,255)
black=(0,0,0)
gray = (230, 230, 230)
dark_gray = (40, 40, 40)
dark_green = (0, 155, 0)
green = (0, 255, 0)
red = (255, 0, 0)
blue = (0, 0, 255)
dark_blue =(0,0, 139)


#定义方向
UP=1
DOWN=2
LEFT=3
RIGHT=4

HEAD=0 #贪吃蛇头部下标
def main():
	pygame.init() #init
	snake_speed_clock=pygame.time.Clock()#创建pygame的时钟对象
	screen=pygame.display.set_mode((windows_width,windows_height)) #创建屏幕
	screen.fill(white)
	pygame.display.set_caption('小王的超级贪吃蛇游戏') #设置标题
	show_start_info(screen) #欢迎信息
	while True:
		running_game(screen, snake_speed_clock)
		show_gameover_info(screen)



def running_game(screen,snake_speed_clock):
	startx=random.randint(3,map_width-8)
	starty=random.randint(3,map_height-8)   #randint(a,b)生成a,b之间的一个任意数
	snake_coords=[{"x":startx,'y':starty}, {'x': startx - 1, 'y': starty}, {'x': startx - 2, 'y': starty}]
	#初始身体坐标
	direction =RIGHT  #c初始移动速度为RIGHT
	food = get_random_location() #事物的随机位置
	background=pygame.image.load('beijing.jpeg').convert()
	while True:
		for event in pygame.event.get():
			if event.type ==QUIT:
				terminate()#用户按下关闭时，退出游戏
			elif event.type ==KEYDOWN:#按下键盘时
				if(event.key==K_LEFT or event.key == K_a)and direction!=RIGHT:
					direction=LEFT
				elif(event.key==K_RIGHT or event.key == K_d)and direction!=LEFT:
					direction=RIGHT
				elif(event.key==K_UP or event.key == K_w)and direction!=DOWN:
					direction=UP
				elif(event.key==K_DOWN or event.key == K_s)and direction!=UP:
					direction=DOWN
				elif event.key==K_ESCAPE:#键入esc退出
					terminate()
		move_snake(direction,snake_coords)
		#移动蛇
		ret = snake_is_alive(snake_coords)
		if not ret :
			break     #蛇死了，游戏结束，下一轮
		snake_is_eat_food(snake_coords,food)
	  #判断蛇是否吃到food
		screen.blit(background,(0,0))
	  #draw_grid(screen)
		draw_snake(screen,snake_coords)
		draw_food(screen,food)
		draw_score(screen,len(snake_coords)-3)#初始长度3
		pygame.display.update()
		snake_speed_clock.tick(snake_speed)#设置最高帧率为snake_speed

def draw_food(screen,food):
	x=food['x']*cell_size
	y=food['y']*cell_size
	appleRect=pygame.Rect(x,y,cell_size,cell_size)
	pygame.draw.rect(screen,red,appleRect)
	appleinnerRect=pygame.Rect(x+3,y+3,cell_size-7,cell_size-7)
	pygame.draw.rect(screen,dark_green,appleinnerRect)

def draw_snake(screen,snake_coords):
	for coord in snake_coords:
		x=coord['x']*cell_size
		y=coord['y']*cell_size
		woemSegmentRect=pygame.Rect(x,y,cell_size,cell_size)
		pygame.draw.rect(screen,dark_blue,woemSegmentRect)
		woeminnerSegmentRect=pygame.Rect(x+4,y+4,cell_size-8,cell_size-8)
		pygame.draw.rect(screen,blue,woeminnerSegmentRect)

#画网格
#def draw_grid(screen):
def move_snake(direction,snake_coords):
	if direction ==UP:
		newHead={'x': snake_coords[HEAD]['x'], 'y': snake_coords[HEAD]['y'] - 1}
	elif direction == DOWN:
		newHead = {'x': snake_coords[HEAD]['x'], 'y': snake_coords[HEAD]['y'] + 1}
	elif direction == LEFT:
		newHead = {'x': snake_coords[HEAD]['x'] - 1, 'y': snake_coords[HEAD]['y']}
	elif direction == RIGHT:
		newHead = {'x': snake_coords[HEAD]['x'] + 1, 'y': snake_coords[HEAD]['y']}
	snake_coords.insert(0,newHead)#插入头

def snake_is_alive(snake_coords):
	tag=True
	if snake_coords[HEAD]['x'] == -1 or snake_coords[HEAD]['x'] == map_width or snake_coords[HEAD]['y'] == -1 or \
			snake_coords[HEAD]['y'] == map_height:
		tag = False  # 蛇碰壁啦
	for snake_body in snake_coords[1:]:
		if snake_body['x'] == snake_coords[HEAD]['x'] and snake_body['y'] == snake_coords[HEAD]['y']:
			tag = False # 蛇碰到自己身体啦
	return tag
def snake_is_eat_food(snake_coords,food):
	if snake_coords[HEAD]['x'] == food['x'] and snake_coords[HEAD]['y'] == food['y']:
		food['x'] = random.randint(0, map_width - 1)
		food['y'] = random.randint(0, map_height - 1) # 实物位置重新设置
	else:
		del snake_coords[-1]  # 如果没有吃到实物, 就向前移动, 那么尾部一格删掉
#食物随机生成
def get_random_location():
	return {'x': random.randint(0, map_width - 1), 'y': random.randint(0, map_height - 1)}
#开始信息
def show_start_info(screen):
	font = pygame.font.Font('myfont.ttf',40)
	tip = font.render('按任意键开始游戏!',True,(0,0,0))
	tip1 = font.render('小王的贪吃蛇', True, (0, 0, 0))
	gamestart =pygame.image.load('start.tif')
	screen.blit(gamestart,(60,30))
	screen.blit(tip,(250,550))
	screen.blit(tip1, (280, 480))
	pygame.display.update()
	while True:
		for event in pygame.event.get():
			if event.type==QUIT:
				terminate()
			elif event.type ==K_ESCAPE:
				terminate()
			elif event.type==KEYDOWN:
				return
#结束信息
def show_gameover_info(screen):
	font=pygame.font.Font('myfont.ttf',40)
	tip = font.render('按Q或ESC退出游戏，按任意键重新开始游戏！',True,(65,105,225))
	gameover =pygame.image.load('gameover.png')
	screen.blit(gameover,(100,100))
	screen.blit(tip,(80,450))
	pygame.display.update()
	while True:
		for event in pygame.event.get():
			if event.type == QUIT:
				terminate()  # 终止程序
			elif event.type == KEYDOWN:
				if event.key == K_ESCAPE or event.key == K_q:  # 终止程序
					terminate()  # 终止程序
				else:
					return  # 结束此函数, 重新开始游戏
def draw_score(screen,score):
	font = pygame.font.Font('myfont.ttf', 30)
	scoreSurf = font.render('得分: %s' % score, True, green)
	scoreRect = scoreSurf.get_rect()
	scoreRect.topleft = (windows_width - 120, 10)
	screen.blit(scoreSurf, scoreRect)

#程序终止
def terminate():
	pygame.quit()
	sys.exit()

main()