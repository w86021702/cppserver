#ifndef __ACCEPTOR_H__
#define __ACCEPTOR_H__

#include "commdef.h"
#include "channel.h"

struct bufferevent;
struct event_base;

namespace CM{

class CAcceptor : public CChannel
{
public:
	CAcceptor(struct event_base *ev_base, int fd, unsigned int port);
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
	struct  bufferevent* _bev;
    struct event_base *_ev_base;
    unsigned int _port;
};

}

#endif
