#ifndef __TOOL_THREAD_QUEUE_H__
#define __TOOL_THREAD_QUEUE_H__

#include <stdio.h>

namespace tool{
namespace thread{

class CQueue
{
public:
    CQueue(unsigned int size = 50);
    ~CQueue();

    int Add(void *arg);
    int Pop(void* front);
    unsigned int Size();
    bool Empty();

private:
    struct QNode
    {
       void *data = NULL;
    };

    QNode *_head;
    volatile unsigned int _tail;
    volatile unsigned int _cur;
    unsigned int _size;
};


}
}



#endif
