#ifndef __WORKER_H__
#define __WORKER_H__

#include "commdef.h"

class CWorker
{
public:
    CWorker();
    ~CWorker();

    pid_t GetPid();

    bool start();
    bool run();

private:

};

#endif
