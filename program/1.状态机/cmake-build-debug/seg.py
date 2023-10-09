import fileinput


#     printf 控制打印格式颜色
#     printf ("\033[0;31;40m    普通输出前景色红色背景色黑色\033[0m\n");
#     printf ("\033[1;32;41m    高亮输出前景色绿色背景色红色\033[0m\n");
#     printf ("\033[4;33;44m    下划线输出前景色黄色背景色蓝色\033[0m\n");
#     printf ("\033[5;36;45m    闪烁输出前景色青色背景色洋红色\033[0m\n");
#     printf ("\033[7;32;47m    反显输出前景色绿色背景色白色\033[0m\n");
#
#     printf("\033[字符串样式；字符串前景颜色号；字符串背景颜色号m 字符串\033[0m\n" );
TEMPLATE = '''
\033[2j\033[1:1f
    AAAAAAAAAAA
    FF       BB
    FF       BB
    FF       BB
    FF       BB
    FF       BB
    GGGGGGGGGGG       
    EE       CC
    EE       CC
    EE       CC
    EE       CC
    EE       CC
    DDDDDDDDDDD
'''

BLOCK={
    0: '\033[37m \033[0m',
    1: '\033[31ma\033[0m',
}
vars="ABCDEFG"


#>>>a='runoob'
#>>> print(globals()) # globals 函数返回一个全局变量的字典，包括所有导入的变量。
# {'__builtins__': <module '__builtin__' (built-in)>, '__name__': '__main__', '__doc__': None, 'a': 'runoob', '__package__': None}
#可以看到变量a是以 字符串'a':'runoob'  用字典方式存储
for i in vars:
    globals()[i]=0     #全局变量，相当于创建了7个全局变量A B C D E F F  后面对其变量赋值就行
stdin=fileinput.input()

while True:
    #exec 执行储存在字符串或文件中的Python语句  exec(stdin.readline())会把命令行输入当作代码段插入到此从运行
    exec(stdin.readline())
    #print(globals()['A'])
    pic=TEMPLATE
    for i in vars:
        pic=pic.replace(i,BLOCK[globals()[i]])  #把A-> BLOCK[globals()[A]  A=0->'\033[37m \033[0m',
    print(pic)