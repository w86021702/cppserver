#include "queue.h"
#include <unistd.h>

using namespace tool::thread;

CQueue::CQueue(unsigned int size)
    : _head(NULL), _tail(0), _cur(0), _size(size)
{
   _head = new QNode[_size];
}

CQueue::~CQueue()
{
    delete[] _head;
}

int CQueue::Add(void *arg)
{
    unsigned int curIdx = 0;
    unsigned int tryCnt = 0;
    do
    {
        if ((_tail + 1)%_size == _cur)
        {
            //队列满了
            return -1;
        }

        if (++tryCnt >= 50)
        {
            sleep(1);
            tryCnt = 0;
        }

        curIdx = _tail;
    }while(!__sync_bool_compare_and_swap(&_tail, curIdx, (curIdx + 1)%_size));

    _head[curIdx].data = (int *)arg;

    return 0;
}

int CQueue::Pop(void* front)
{
    unsigned int curIdx = 0;
    unsigned int tryCnt = 0;
    do
    {
        if ((_cur)%_size == _tail)
        {
            //empty
            return -1;
        }

        if (++tryCnt >= 50)
        {
            sleep(1);
            tryCnt = 0;
        }

        curIdx = _cur;
    }while(!__sync_bool_compare_and_swap(&_cur, curIdx, (curIdx + 1)%_size));

    front = _head[curIdx].data;
    _head[curIdx].data = NULL;

    return 0;
}

unsigned int CQueue::Size()
{
    return _size;
}

bool CQueue::Empty()
{
    return _tail == _cur;
}
