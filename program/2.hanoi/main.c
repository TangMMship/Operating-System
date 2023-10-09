#include <stdio.h>

//a b c 三个柱子 n个大小递减的盘子(a柱子上)->c柱子上  a(n)->c
//n个盘子,总是需要将大盘子上面的盘子放到中介柱子b,再转移大盘子到目标柱子
//要将大盘子上的(n-1)个盘子放到中介柱子,就相当于把问题简化为a(n-1)->b
//同理,就需要将n-2个盘子放到此时中介柱子c上才能把次大小的盘子转移到目标柱子...
//如此递归将n-1个盘子放到中介柱子后，再将大盘子放到目标柱子，再将中介柱子的n-1个盘子放到目标柱子 b(n-1)->c继续递归
void hano(int n,char from,char to,char via)
{
    if(n==1)printf("%c->%c\n",from,to);
    else
    {
        hano(n-1,from,via,to);
        hano(1,from,to,via);
        hano(n-1,via,to,from);
    }
    return;
}
int main()
{
    hano(5,'a','b','c');
    return 0;
}
