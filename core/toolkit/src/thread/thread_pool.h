#ifndef __TOOL_THREAD_POOL__
#define __TOOL_THREAD_POOL__

//用户级线程
//支持协程

namespace tool{
namespace thread{

class CThreadPool
{
public:
    CThreadPool(unsigned int size = 5);
    ~CThreadPool();

private:
    unsigned int _size;
};

}}

#endif

