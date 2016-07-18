#ifndef __TOOL_THREAD_QUEUE_H__
#define __TOOL_THREAD_QUEUE_H__

#include <iostream>

namespace tool{
namespace thread{

class CQueue
{
public:
    CQueue(unsigned int size = 50);
    ~CQueue();

    int Push(void* arg);

    //由调用方管理front内存
    int Pop(void* front);
    unsigned int Size();
    bool Empty();

private:
    struct QNode
    {
        void *data = NULL;
    };

    QNode *_head;
    volatile unsigned int _cur;
    volatile unsigned int _tail;
    unsigned int _size;
};


}
}



#endif
