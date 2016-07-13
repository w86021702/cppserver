#include "coroutine.h"
#include <ucontext.h>

#include <stdio.h>

ucontext uctx_f1, uctx_main;
char f1_st[16384];

void fun1()
{
    //int ret = getcontext(&uctx_f1);
    //if (ret != 0)
    //{
    //    printf("%s getcontext fail\n", __func__);
    //    return ;
    //}

    printf("%s  begin, uctx_f1:%s\n", __func__, (char*)uctx_f1.uc_stack.ss_sp);
    if (-1 == swapcontext(&uctx_f1, &uctx_main))
    {
        printf("%s swapcontext fail\n", __func__);
        return ;
    }

    printf("%s  end, uctx_f1:%s\n", __func__, (char*)uctx_f1.uc_stack.ss_sp);
}

int main(int argc, char** argv)
{
    int ret = getcontext(&uctx_f1);
    if (ret != 0)
    {
        printf("getcontext fail\n");
        return -1;
    }

    uctx_f1.uc_stack.ss_sp = f1_st; 
    uctx_f1.uc_stack.ss_size = sizeof(f1_st); 
    uctx_f1.uc_link = &uctx_main; 
    makecontext(&uctx_f1, fun1, 0);
    
    if (-1 == swapcontext(&uctx_main, &uctx_f1))
    {
        printf("%s swapcontext fail\n", __func__);
        return -1;
    }
    printf("end!\n");

    //必须重新make, f1堆栈已经变化
    //makecontext(&uctx_f1, fun1, 0);
    if (-1 == swapcontext(&uctx_main, &uctx_f1))
    {
        printf("%s swapcontext fail\n", __func__);
        return -1;
    }
    printf("end2!\n");
    return 0;
}
