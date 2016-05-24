#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "commdef.h"

struct bufferevent;
struct event_base;

namespace CM{

class CChannel
{
public:
	CChannel(struct event_base *ev_base, int fd);
	~CChannel();

	virtual int HandleRead(char* buf, unsigned int len);
	void HandleWrite();
	void OnError();
	virtual int HandleOut(char* buf, unsigned int len);
    int GetSocketFd();

private:
	int _fd;
	struct  bufferevent* _bev;
};

//class CAcceptor
//{
//public:
//    CAcceptor();
//    ~CAcceptor();
//
//    int Accept();
//
//private:
//    int _fd;
//};

}

#endif
