#include <stdio.h>
#include <unistd.h>

#if 0
#define regs_foreach(_) _(x) _(y)
#define run_logic x1=!x && y;\
                  y1=!x && !y;
#define DEFINE(x) static int x,x##1;
#define UPDATE(x) x=x##1;
#define PRINTF(x) printf(#x"=%d;",x);

int main() {
    regs_foreach(DEFINE);
    while(1)
    {
        run_logic;
        regs_foreach(UPDATE);
        regs_foreach(UPDATE);
        regs_foreach(PRINTF);
        printf("\n");
        sleep(1);
    }
    return 0;
}
#endif

#if 0
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
        fflush(stdout);
        sleep(1);
    }
    return 0;
}

#endif


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

