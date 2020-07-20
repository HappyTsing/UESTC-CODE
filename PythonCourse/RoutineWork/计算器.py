from tkinter import *
from tkinter.ttk import *
def my_frame(master):
    w=Frame(master)
    w.pack(side=TOP,expand=YES,fill=BOTH)
    return w


def my_button(master,text,command):
    w=Button(master,text=text,command=command,width=6)
    w.pack(side=LEFT,expand=YES,fill=BOTH,padx=2,pady=2)
    return w


def back(text):
    if len(text)>0:
        return text[:-1]
    else:
        return text


def calc(text):
    try:
        if sep_flag.get()==0:
            return eval(del_sep(text))
        else:
            return add_sep(str(eval(del_sep(text))))
    except(SyntaxError,ZeroDivisionError,NameError):
        return 'Error'


def add_sep(text):
    dot_index=text.find('.')
    if dot_index>0:
        text_head=text[:dot_index]
        text_tail=text[dot_index:]
    elif dot_index<0:
        text_head=text
        text_tail=''
    else:
        text_head=''
        text_tail=text
    list_=[char for char in text_head]
    length=len(list_)
    tmp_index=3
    while length-tmp_index>0:
        list_.insert(length-tmp_index,',')
        tmp_index+=3
    list_.extend(text_tail)
    new_text=''
    for char in list_:
        new_text+=char
    return new_text
def del_sep(text):
    return text.replace(',','')


wind=Tk()
wind.title('简易计算器')
main_menu=Menu(wind)
calc_menu=Menu(main_menu,tearoff=0)
calc_menu.add_command(label='退出',command=lambda:exit())
main_menu.add_cascade(label='计算',menu=calc_menu)
text=StringVar()
sep_flag=IntVar()
sep_flag.set(0)
view_menu=Menu(main_menu,tearoff=0)
view_menu.add_checkbutton(label='显示千位分隔符',variable=sep_flag,\
                          command=lambda t=text:t.set(add_sep(t.get())))
main_menu.add_cascade(label='视图',menu=view_menu)
wind['menu']=main_menu

Entry(wind,textvariable=text).pack(expand=YES,fill=BOTH,\
                                   padx=2,pady=4)

style=Style()
style.configure('TButton',padding=3)
fedit=my_frame(wind)
my_button(fedit,'Backspace',lambda t=text:t.set(back(t.get())))
my_button(fedit,'Clear',lambda t=text:t.set(''))
my_button(fedit,'±',lambda t=text:t.set('-('+t.get()+')'))

for key in('789/','456*','123-','0.=+'):
    fsymb=my_frame(wind)
    for char in key:
        if char=='=':
            my_button(fsymb,char,\
                      lambda t=text:t.set(calc(t.get())))
        else:
            my_button(fsymb,char,\
                      lambda t=text,c=char:set(t.get()+c))


wind.mainloop()
