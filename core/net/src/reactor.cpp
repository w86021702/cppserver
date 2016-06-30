#include "reactor.h"
#include "client.h"
#include "event2/util.h"
#include "event2/event.h"
#include <string.h>

using namespace CM;

void on_acceptor(evutil_socket_t fd, short event, void *arg);

CReactor::CReactor()
{
    _evBase = event_base_new();
}

CReactor::~CReactor()
{
	if (_evBase)
		event_base_free(_evBase);
	_evBase = NULL;
}

int CReactor::RegisterHandler(int handlerID, void *args)
{
    auto* channel = (CChannel*)args;
    channel->SetReactor(this);
    //channel->
    
    return 0;
}

int CReactor::RemoveHandler(int handlerID)
{
    return 0;
}

int MakeListener(const std::string& ip, unsigned int port)
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

    if ( 0 != evutil_make_socket_nonblocking(listenFd) )
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
    printf("make listen11 %d\n", listenFd);

    //struct event *listen_ev = event_new(ev_base, listenFd, EV_READ | EV_PERSIST | EV_ET, on_acceptor, ev_base);
    //event_add(listen_ev, NULL);
    return 0;
}

int CReactor::OnLoop()
{
    event_base_loop(_evBase, 0x04);

    //释放ev_base所有事件
    event_base_free(_evBase);
    return 0;
}

int CReactor::OnLoop(const std::string& ip, unsigned int port)
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

    if ( 0 != evutil_make_socket_nonblocking(listenFd) )
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
    printf("loop listen %d\n", listenFd);

    struct event_base *ev_base = event_base_new();
    struct event *listen_ev = event_new(ev_base, listenFd, EV_READ | EV_PERSIST | EV_ET, on_acceptor, ev_base);

    event_add(listen_ev, NULL);

    //循环
    //event_base_dispatch(ev_base); 没有事件时会退出
    event_base_loop(ev_base, 0x04);

    //释放ev_base所有事件
    event_base_free(ev_base);
    event_free(listen_ev);

    return 0;
}

void on_acceptor(evutil_socket_t fd, short event, void *arg)
{
    printf("on accept\n");
    struct sockaddr_in addr;
    socklen_t len = 0;
    while (1)
    {
        evutil_socket_t newFd = accept(fd, (struct sockaddr*)&addr, &len);
        if (newFd <= 0)
        {
            break;
        }

        printf("accept create new_bufferev fd:%d\n", newFd);
        auto* channel = new CClient((event_base*)arg, newFd);
        //set reactor
    }
}
void* CReactor::GetReactor() const
{
	return _evBase;
}

void* CReactor::GetLoop() const
{
	return _evBase;
}
