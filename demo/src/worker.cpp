#include "worker.h"
#include "reactor.h"

CWorker::CWorker()
{
}

CWorker::~CWorker()
{
}

pid_t CWorker::GetPid()
{
    return getpid();
}

bool CWorker::start()
{
    if (fork() > 0)
    {
        //parent
        return true;
    }


    CReactor reactor;
    reactor.OnLoop();

    return true;
}
