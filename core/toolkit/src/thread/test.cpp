#include "coroutine.h"
#include <ucontext.h>

#include <stdio.h>
#include "coroutine.cpp"

//ucontext uctx_f1, uctx_main;
//char f1_st[16384];
//
//void fun1()
//{
//    //int ret = getcontext(&uctx_f1);
//    //if (ret != 0)
//    //{
//    //    printf("%s getcontext fail\n", __func__);
//    //    return ;
//    //}
//
//    printf("%s  begin, uctx_f1:%s\n", __func__, (char*)uctx_f1.uc_stack.ss_sp);
//    if (-1 == swapcontext(&uctx_f1, &uctx_main))
//    {
//        printf("%s swapcontext fail\n", __func__);
//        return ;
//    }
//
//    printf("%s  end, uctx_f1:%s\n", __func__, (char*)uctx_f1.uc_stack.ss_sp);
//}
//
//int test(int argc, char** argv)
//{
//    int ret = getcontext(&uctx_f1);
//    if (ret != 0)
//    {
//        printf("getcontext fail\n");
//        return -1;
//    }
//
//    uctx_f1.uc_stack.ss_sp = f1_st; 
//    uctx_f1.uc_stack.ss_size = sizeof(f1_st); 
//    uctx_f1.uc_link = &uctx_main; 
//    makecontext(&uctx_f1, fun1, 0);
//    
//    if (-1 == swapcontext(&uctx_main, &uctx_f1))
//    {
//        printf("%s swapcontext fail\n", __func__);
//        return -1;
//    }
//    printf("end!\n");
//
//    //必须重新make, f1堆栈已经变化
//    //makecontext(&uctx_f1, fun1, 0);
//    if (-1 == swapcontext(&uctx_main, &uctx_f1))
//    {
//        printf("%s swapcontext fail\n", __func__);
//        return -1;
//    }
//    printf("end2!\n");
//    return 0;
//}

CCorutineSchedule * cs = new CCorutineSchedule();
void f1(void *arg)
{
    printf("%s begin\n", __func__);
    printf("f1~!!!!!\n");
    cs->Yield();
    printf("%s end!!!!\n", __func__);
}

void f2(void *arg)
{
    printf("%s begin\n", __func__);
    printf("f2~!!!!!\n");
    cs->Yield();
    printf("%s end\n", __func__);
}

int test2(int argc, char** argv)
{
    cs->CreateCorutine(f1, NULL);
    cs->CreateCorutine(f2, NULL);

    cs->ResumeCoroutine(f1, NULL);
    cs->ResumeCoroutine(f1, NULL);
    //ResumeCoroutine(f1, NULL);
    return 0;
}

int main(int argc, char** argv)
{
    test2(argc, argv);
    return 0;
}

