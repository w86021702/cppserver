#ifndef __CHANNEL_H__
#define __CHANNEL_H__

#include "commdef.h"

namespace CM{

struct bufferevent;

class CChannel
{
public:
	CChannel();
	~CChannel();

	int HandleRead(char* buf, unsigned int len);
	void HandleWrite();
	void OnError();
	int HandleOut(char* buf, unsigned int len);

private:
	int _fd;
	struct  bufferevent* bev;
};

}

#endif
