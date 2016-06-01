#ifndef __REACTOR_H__
#define __REACTOR_H__

#include "commdef.h"

class CReactor
{
public:
	CReactor();
	~CReactor();

    int RegisterHandler(int handlerID, void *args);
    int RemoveHandler(int handlerID);
	int OnLoop(const std::string& ip = "127.0.0.1", unsigned int port = 9094);

private:
};

#endif
