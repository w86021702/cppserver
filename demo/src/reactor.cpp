#include "reactor.h"
#include "channel.h"
#include "event2/util.h"
#include "event2/event.h"
#include <string.h>

using namespace CM;

void on_acceptor(evutil_socket_t fd, short event, void *arg);

CReactor::CReactor()
{
}

CReactor::~CReactor()
{
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
    printf("listen %d\n", listenFd);

    struct event_base *ev_base = event_base_new();
    struct event *listen_ev = event_new(ev_base, listenFd, EV_READ | EV_PERSIST | EV_ET, on_acceptor, ev_base);

    event_add(listen_ev, NULL);

    //循环
    //event_base_dispatch(ev_base); 没有事件时会退出
    event_base_loop(ev_base, 0x04);

    //释放ev_base所有事件
    event_base_free(ev_base);

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
        auto* channel = new CChannel((event_base*)arg, newFd);
    }
}
