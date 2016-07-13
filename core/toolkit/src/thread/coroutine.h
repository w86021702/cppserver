#ifndef __TOOL_COROUTINE_H__
#define __TOOL_COROUTINE_H__

#include <ucontext.h>

namespace Tool{
namespace Thread{

class CCorutineSchedule
{
public:
    int AddCorutine(void (*func)(void*), void* arg);
    int Yield();
    int ResumeCoroutine();


private:
    unsigned int _running;
};

}}

#endif
