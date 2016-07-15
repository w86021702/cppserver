#include "coroutine.h"
#include <stdio.h>
#include <string.h>

using namespace Tool::Thread;

CCorutineSchedule::CCorutineSchedule()
{
}

CCorutineSchedule::~CCorutineSchedule()
{
    for (auto iter : _coroutines)
    {
        delete iter.second;
    }
    _coroutines.clear();
}

int CCorutineSchedule::__GetFunAddr(Fun fun)
{
    char tmp[1024];
    int addr;
    //memcpy((char*)&addr, (const void*)fun, sizeof(addr));
    snprintf(tmp, sizeof(tmp), "%d", fun);
    addr = atoi(tmp);
    printf("%s addr:%d fun:%d\n", __func__, addr, fun);
    return addr;
}

void CCorutineSchedule::__Begin(void *arg)
{
    printf("##%s begin\n", __func__);
    CCorutineSchedule* sch = (CCorutineSchedule*)arg;
    auto iter = sch->_coroutines.find(sch->_curfunc);
    if (iter == sch->_coroutines.end())
    {
        printf("%s find not addr %d\n", __func__, sch->_curfunc);
        return ;
    }

    SCoroutine& crtine = *(iter->second);
    sch->_curfunc = crtine.id;
    crtine.state = ECoroutine_Runing;
    crtine.fun(crtine.arg);

    crtine.state = ECoroutine_Free;
    sch->_curfunc = -1;
    printf("##%s end\n", __func__);
}

int CCorutineSchedule::CreateCorutine(Fun fun, void *arg)
{
    SCoroutine* thread = new SCoroutine();
    memset(thread, 0, sizeof(thread));
    int ret = getcontext(&thread->ctx);
    if (ret != 0)
    {
        printf("getcontext fail\n");
        return -1;
    }

    thread->id = __GetFunAddr(fun);
    thread->fun = fun;
    thread->state = ECoroutine_Ready;
    thread->arg = arg;
    ucontext& uctx_f = thread->ctx;
    uctx_f.uc_stack.ss_sp = thread->stack; 
    uctx_f.uc_stack.ss_size = sizeof(thread->stack); 
    uctx_f.uc_link = &_uctx_main; 
    makecontext(&uctx_f, (void (*)())CCorutineSchedule::__Begin, 1, this);
    _coroutines[thread->id] = thread;
    printf("%s, func: %d  threadId:%d\n", __func__, fun, thread->id);

    return 0;
}

int CCorutineSchedule::Yield()
{
    printf("%s curfunc %d\n", __func__, _curfunc);
    
    auto iter = _coroutines.find(_curfunc);
    if (iter == _coroutines.end())
    {
        printf("%s find not addr %d\n", __func__, _curfunc);
        return -1;
    }

    if (_curfunc != -1)
    {
        _curfunc = -1;
        SCoroutine& crtine = *(iter->second);
        crtine.state = ECoroutine_Suspend;
        printf("%s swapcontext(&crtine.ctx, &_uctx_main)\n", __func__);
        if (-1 == swapcontext(&crtine.ctx, &_uctx_main))
        {
            printf("%s swapcontext fail\n", __func__);
            return -1;
        }
    }

    printf("%s end\n", __func__);

    return 0;
}

int CCorutineSchedule::ResumeCoroutine(Fun fun, void* arg)
{
    printf("%s begin\n", __func__);
    auto iter = _coroutines.find(__GetFunAddr(fun));
    if (iter == _coroutines.end())
    {
        printf("%s find not addr %d\n", __func__, __GetFunAddr(fun));
        return -1;
    }

    SCoroutine& crtine = *(iter->second);
    if (crtine.state == ECoroutine_Free)
    {
        printf("%s is free\n", __func__);
        return -1;
    }

    //if (crtine.state == ECoroutine_Ready)
    //{
    //}
    //else if (crtine.state == ECoroutine_Suspend)
    //{
    //    if (-1 == swapcontext(&_uctx_main, &crtine.ctx))
    //    {
    //        printf("%s swapcontext fail\n", __func__);
    //        return -1;
    //    }
    //}

    printf("%s curfunc addr %d, func addr %d\n", __func__, _curfunc, __GetFunAddr(fun));
    _curfunc = __GetFunAddr(fun);

    printf("%s swapcontext(&_uctx_main, &crtine.ctx)\n", __func__);
    if (-1 == swapcontext(&_uctx_main, &crtine.ctx))
    {
        printf("%s swapcontext fail\n", __func__);
        return -1;
    }

    printf("%s end\n", __func__);
    return 0;
}

bool CCorutineSchedule::IsAlive(Fun fun)
{
    auto iter = _coroutines.find(__GetFunAddr(fun));
    if (iter == _coroutines.end())
    {
        printf("%s find not addr %d\n", __func__, __GetFunAddr(fun));
        return false;
    }

    if (iter->second->state == ECoroutine_Free)
    {
        return false;
    }

    return true;
}

bool CCorutineSchedule::IsAllFinsh()
{
    for (const auto& iter : _coroutines)
    {
        const auto& coroutine = *(iter.second);
        if (coroutine.state != ECoroutine_Free)
        {
            return false;
        }
    }
    return true;
}
