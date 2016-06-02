#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "commdef.h"

struct bufferevent;
struct event_base;

namespace CM{

class CChannel
{
public:
	CChannel(int fd);
	~CChannel();

	virtual int HandleRead() = 0;
	virtual int HandleWrite() = 0;
	virtual void OnError() = 0;
	virtual int HandleOut(char* buf, unsigned int len);
    virtual int HandleClose();
    int GetSocketFd();
    virtual int SetReactor(void* reactor) = 0;
    void* GetReactor() const;

protected:
	int _fd;
};

}

#endif
