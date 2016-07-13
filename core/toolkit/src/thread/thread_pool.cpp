#include "thread_pool.h"

using namespace tool::thread;

CThreadPool::CThreadPool(unsigned int size)
    :_size(size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        //pthread_create();
    }
}

CThreadPool::~CThreadPool()
{

}
