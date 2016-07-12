#ifndef __TOOL_THREAD_TASK_H__
#define __TOOL_THREAD_TASK_H__

namespace tool{
namespace thread{

class ITask
{
public:
    ITask(){}
    virtual ~ITask(){}

    virtual int Run(void* arg) = 0;

private:

};

}

#endif
