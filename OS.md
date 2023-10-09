## 一、操作系统概述

### 1.1 操作系统是什么

**操作系统是管理软硬件资源，为程序提供服务**的程序



### 1.2基础补充

#### 1.2.1 c语言宏定义详解

1. **简单的宏定义**

   格式：**#define <宏名/标识符> <字符串>**

   eg:#define PI 3.1415926

   

2.  **带参数的宏定义（除了一般的字符串替换，还要做参数代换）**

   格式：#define <宏名>(<参数表>) <字符串>

   eg:#define S(a,b) a*b

   area=S(3,2);

3. **如果要写宏不止一行，则在结尾加反斜线符号使得多行能连接上，如：**

   ```c
   #define HELLO "hello \
   the world"
   ```

4. **# 运算符**

   比如如果我们宏定义了：

   ```c
   #define SUM (a,b) ((a) + (b)) 
   ```

   我们想要输出“1 + 2 + 3 + 4 = 10”，用以下方式显得比较麻烦，有重复代码，而且中间还有括号：

   ```c
   printf("(%d + %d) + (%d + %d) = %d\n", 1, 2, 3, 4, SUM(1 + 2, 3+ 4));
   ```

   那么这时可以考虑用 # 运算符来在字符串中包含宏参数，# 运算符的用处就是把语言符号转化为字符串。例如，如果 a 是一个宏的形参，则替换文本中的 #a  则被系统转化为 “a”。而这个转化的过程成为 “字符串化（stringizing）”。用这个方法实现上面的要求：

   ```c
   #define SUM(a,b) printf(#a " + "#b" = %d\n",((a) + (b)))    //宏定义，运用 # 运算符
   SUM(1 + 2, 3 + 4);                                          //宏调用
   //输出结果：1 + 2 + 3 + 4 = 10
   ```

   调用宏时，用 1 + 2 代替 a，用 3 + 4 代替b，则替换文本为：printf(“1 + 2” ” + ” “3 + 4” ” = %d\n”,((1 + 2) + (3 + 4)))，接着字符串连接功能将四个相邻的字符串转换为一个字符串：

   ```c
   "1 + 2 + 3 + 4 = %d\n"
   ```

5. **## 运算符**

   和 # 运算符一样，## 运算符也可以用在替换文本中，而它的作用是起到粘合的作用，即将两个语言符号组合成一个语言符号，所以又称为“预处理器的粘合剂（Preprocessor Glue）”。用法：

   ```c
   #define NAME(n) num ## n            //宏定义，使用 ## 运算符
   int num0 = 10;
   printf("num0 = %d\n", NAME(0));     //宏调用
   ```

   NAME(0)被替换为 num ## 0，被粘合为： num0。



### 1.3 状态机

```
//定义寄存器 _就代替后面要对x后y要进行的操作 eg: REGS_FOREACH(PRINT); 就意味着PRINT(x) PRINT(y)
#define REGS_FOREACH(_)  _(X) _(Y)
#define RUN_LOGIC        X1 = !X && Y; \
                         Y1 = !X && !Y;
#define DEFINE(X)        static int X, X##1;
#define UPDATE(X)        X = X##1;
#define PRINT(X)         printf(#X " = %d; ", X);

int main() {
  REGS_FOREACH(DEFINE);
  while (1) { // clock
    RUN_LOGIC;
    REGS_FOREACH(PRINT);
    REGS_FOREACH(UPDATE);
    putchar('\n'); sleep(1);
  }
}

//宏定义语句定义的是一段语句记得加分号
```

数码管

![Screenshot_20231008_210214](./assets/Screenshot_20231008_210214.jpg)

```
#define regs_foreach(_) _(x) _(y)
#define out_foreach(_) _(A) _(B) _(C) _(D) _(E) _(F) _(G)
#define run_logic x1=!x && y; \
                  y1=!x && !y; \
                  A=(!x && !y)||(x&&!y); \
                  B=1; \
                  C=(!x && !y)||(!A&&B); \
                  D=(!x && !y)||(x&&!y); \
                  E=(!x && !y)||(x&&!y); \
                  F=!x && !y; \
                  G=x&&!y;
#define DEFINE(x) static int x,x##1;
#define UPDATE(x) x=x##1;
#define PRINTF(x) printf(#x"=%d;",x);

int main() {
    out_foreach(DEFINE);
    regs_foreach(DEFINE);
    while(1)
    {
        run_logic;
        regs_foreach(UPDATE);
        regs_foreach(UPDATE);
        out_foreach(PRINTF);
        putchar('\n');
        fflush(stdout);  //为什么用fprint(stdout,#x"=%d;",x);不行
        sleep(1);
    }
    return 0;
}
```

c语言也是状态机：

状态：堆和栈                   上面的状态机的状态：0 、1、 2

初始状态：main语句的第一句	上面状态机的初始状态：0

迁移：串行执行语句			上面状态机迁移 0->1->2->0

mount -o remount -rw /var/snap/firefox/common/host-hunspell
