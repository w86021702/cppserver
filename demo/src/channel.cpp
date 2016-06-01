#include "channel.h"
#include "event2/util.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include <assert.h>

using namespace CM;

void channel_readcb(struct bufferevent *bev, void *ptr);
void writecb(struct bufferevent *bev, void *ptr);
void event_cb(struct bufferevent *bev, short event, void *arg);

CChannel::CChannel(struct event_base *ev_base, int fd)
    :_fd(fd), _ev_base(ev_base)
{
    assert(ev_base != NULL && fd > 0);

	_bev = bufferevent_socket_new(ev_base, fd, BEV_OPT_CLOSE_ON_FREE);
	assert(_bev);
    bufferevent_setcb(_bev, channel_readcb, NULL, event_cb, this);
	//设置低水位
	bufferevent_setwatermark(_bev, EV_READ, sizeof(unsigned int), 0);
    bufferevent_enable(_bev, EV_READ | EV_ET | EV_PERSIST);
}

CChannel::~CChannel()
{
    if (_bev != NULL)
    {
        bufferevent_free(_bev);
        _bev = NULL;
    }
}

int CChannel::HandleRead(char* buf, unsigned int len)
{
	return 0;
}

void CChannel::HandleWrite()
{
}

void CChannel::OnError()
{
}

int CChannel::HandleOut(char* buf, unsigned int len)
{
	printf("###recv:%s\n", buf);
	//解析协议
	return 0;
}

int CChannel::GetSocketFd()
{
	return _fd;
}

void CChannel::HandleClose()
{
    //delete this;
}

void channel_readcb(struct bufferevent *bev, void *ptr)
{
    printf("on read!buf:\n");
	struct evbuffer *input = bufferevent_get_input(bev);
	unsigned int len = evbuffer_get_length(input);
	while(len >= sizeof(unsigned int))
	{
		unsigned int len = evbuffer_get_length(input);
		//包头大小未知
		if (len < 4)
			return ;

		unsigned int code = 0;
		size_t size = evbuffer_copyout(input, &code, sizeof(unsigned int));
		printf("code:%d\n", code);
		//code = ntohl(code);
		printf("after code:%d\n", code);
		if ( size < sizeof(unsigned int) )
		{
			printf("log size :%u, fail\n", code);
			return ;
		}

		char req[4096];
		unsigned int reqLen = size + code;
		printf("reqLen lower:%u\n", reqLen);
		if (len >= reqLen)
		{
			//int removeLen = evbuffer_copyout(input, req, reqLen);
			int removeLen = evbuffer_remove(input, req, reqLen);
			if (-1 == removeLen)
			{
				printf("remove fail\n");
				return ;
			}
			printf("remove len %d \n", removeLen);
			CChannel *channel = (CChannel*)ptr;
			int ret = channel->HandleOut(req+size, reqLen - size);
			if ( 0 != ret )
			{
				printf("%s HandleOut error\n", __func__ );
			}

			//debug
			len = evbuffer_get_length(input);
			printf("after remove len:%d\n", len);
		}
		else
		{
			return ;
		}
	}
}

void writecb(struct bufferevent *bev, void *ptr)
{
}

void event_cb(struct bufferevent *bev, short event, void *arg)
{
	if (event & BEV_EVENT_EOF)
		printf("connection closed\n");
	else if (event & BEV_EVENT_ERROR)
		printf("some other error\n");

	//这将自动close套接字和free读写缓冲区
	//bufferevent_free(bev);
	delete (CChannel *)arg;
}
