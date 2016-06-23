#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "commdef.h"
#include "channel.h"

struct event_base;
struct event;

namespace CM{

class CAcceptor : public CChannel
{
public:
	CAcceptor(int fd, unsigned int port);
	~CAcceptor();

	virtual int HandleRead();
	virtual int HandleWrite();
	void OnError();
	virtual int HandleOut(char* buf, unsigned int len);
    virtual int HandleClose();
    int GetSocketFd();
    virtual int SetReactor(void* reactor);
    void* GetReactor() const;

private:
    struct event_base *_ev_base;
    unsigned int _port;
	struct event *_listen_ev;
    void *_reactor;
};

}

#endif
