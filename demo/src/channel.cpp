#include "channel.h"
#include "event2/bufferevent.h"

using namespace CM;

void readcb(struct bufferevent *bev, void *ptr);
void writecb(struct bufferevent *bev, void *ptr);

CChannel::CChannel()
{
}

CChannel::~CChannel()
{
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
	return 0;
}

void readcb(struct bufferevent *bev, void *ptr)
{
    printf("on read!buf:\n");
	struct evbuffer *input = bufferevent_get_input(bev);
	int len = evbuffer_get_length(input);
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
		handleout(req+size, reqLen - size);

		//debug
		len = evbuffer_get_length(input);
		printf("after remove len:%d\n", len);
	}
}

void writecb(struct bufferevent *bev, void *ptr)
{
}

