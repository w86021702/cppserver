#include "cas_queue.h"

using namespace tool;

CCASQueue::CCASQueue(unsigned int size)
    :_begin(NULL), _next(NULL), _tail(NULL), _size(size)
{
    if (size == 0)
    {
        return ;
    }

    _begin = new int[size];
}
