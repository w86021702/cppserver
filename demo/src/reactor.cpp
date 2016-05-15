#include "reactor.h"

void readcb(struct bufferevent *bev, void *ptr);
void writecb(struct bufferevent *bev, void *ptr);

CReactor::CReactor()
{
}

CReactor::~CReactor()
{
}

void CReactor::OnLoop(const std::string& ip, unsigned int port)
{
    evutil_socket_t listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if ( listenFd < 0 )
    {
        printf("socket error");
        return -1;
    }

    sockaddr_in seraddr;
    memset(&seraddr, 0, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(port);

    if ( 0 != set_socket_nonblock(listenFd) )
    {
        printf("socket error\n");
        return -1;
    }

    if ( bind(listenFd, (sockaddr *)&seraddr, sizeof(seraddr)) < 0 )
    {
        printf("bind fail\n");
        return -1;
    }

    if ( listen(listenFd, 10) < 0 )
    {
        printf("listen fail\n");
        return -1;
    }
    printf("listen %d\n", listenFd);

    struct event_base *ev_base = event_base_new();
    struct event *listen_ev = event_new(ev_base, listenFd, EV_READ | EV_PERSIST, on_accept, NULL);
	g_base = ev_base;

    event_add(listen_ev, NULL);

    //循环
    //event_base_dispatch(ev_base); 没有事件时会退出
    event_base_loop(ev_base, 0x04);

    //释放ev_base所有事件
    event_base_free(ev_base);

}

void readcb(struct bufferevent *bev, void *ptr)
{
    printf("on read!buf:\n");
	struct evbuffer *input = bufferevent_get_input(bev);
	int len = evbuffer_get_length(input);
	//包头大小未知
	if (len < sizeof(unsigned int))
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
		//handleout(req+size, reqLen - size);

		//debug
		len = evbuffer_get_length(input);
		printf("after remove len:%d\n", len);
	}
}

void writecb(struct bufferevent *bev, void *ptr)
{
}
