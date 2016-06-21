#include "worker.h"
#include "reactor.h"
#include "acceptor.h"
#include <sys/socket.h>

using namespace CM;

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

    run();
    return true;
}

bool CWorker::run()
{
    printf("worker begin\n");
    unsigned int _port = 9094;
    int listenFd = socket(AF_INET, SOCK_STREAM, 0);
    CAcceptor acceptor(listenFd, _port);

    CReactor reactor;
    reactor.RegisterHandler(listenFd, &acceptor);
    reactor.OnLoop();
    return true;
}
