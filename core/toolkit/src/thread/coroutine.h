#ifndef __TOOL_COROUTINE_H__
#define __TOOL_COROUTINE_H__

//makecontext和swapcontext协程调度器

#include <map>
#include <ucontext.h>

namespace Tool{
namespace Thread{

#define CORUTINE_STACK_SIZE 1024*128
typedef void (*Fun)(void*);

const unsigned int MAX_CORUTINE_ID = 65536;

class CCorutineSchedule
{
public:
    enum ECoroutineState
    {
        ECoroutine_Ready = 1,
        ECoroutine_Runing = 2,
        ECoroutine_Suspend = 3,
        ECoroutine_Free = 4,
    };

    struct SCoroutine
    {
        unsigned int id = 0;
        Fun fun = NULL;
        void *arg = NULL;
        ucontext ctx;
        char stack[CORUTINE_STACK_SIZE];
        ECoroutineState state;
    };

public:
    CCorutineSchedule();
    ~CCorutineSchedule();
    int CreateCorutine(Fun func, void* arg);
    int RemoveCorutine(unsigned int coroutineID);
    int Yield();
    int ResumeCoroutine(unsigned int coroutineID);
    bool IsAlive(unsigned int coroutineID);
    bool IsAllFinsh();

private:
    int __GetFunAddr(Fun fun);
    int __ClearAllFree();
    int __AllocCoroutinedId();
    static void __Begin(void *arg);

private:
    std::map<int, SCoroutine*> _coroutines;
    ucontext _uctx_main;
    int _curfunc = -1;
    unsigned int _usefulCoroutineId = 0;
};

}}

#endif
