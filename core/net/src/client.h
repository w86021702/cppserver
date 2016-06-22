#ifndef __CLIENT_H__
#define __CLIENT_H__

#include "commdef.h"
#include "channel.h"

struct bufferevent;
struct event_base;

namespace CM{

class CClient : public CChannel
{
public:
	CClient(struct event_base *ev_base, int fd);
	~CClient();

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
};

}

#endif
