#ifndef __CAS_QUEUE_H__
#define __CAS_QUEUE_H__

#include "commdef.h"

namespace tool{

class CCASQueue
{
public:
    CCASQueue(unsigned int size = 0);
    ~CCASQueue();

    void* Get();
    bool Add(void* arg);
    bool Pop();

private:
    void *_begin;
    void *_next;
    void *_tail;
    unsigned int _size;
};

typedef CCASQueue CCASQue;

}

#endif

