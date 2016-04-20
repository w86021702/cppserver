#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <fcntl.h>
#include <time.h>

void showUsage()
{
    printf("-t ip -p port\n");
}

void on_accept(evutil_socket_t fd, short event, void *arg)
{
}

void on_read(evutil_socket_t fd, short event, void *arg)
{
}

int set_socket_nonblock(evutil_socket_t& fd)
{
    //设置非阻塞
    int flags = fcntl(fd, F_GETFL, 0);
    if ( flags < 0 )
    {
        printf("socket error");
        return -1;
    }
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    return 0;
}

void make_buffer_event(struct event_base *ev_base)
{
    evutil_socket_t fd;
    if ( 0 != set_socket_nonblock(fd) )
    {
        return ;
    }
    struct bufferevent *bev;
    bev = bufferevent_socket_new(ev_base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_enable(bev, EV_READ | EV_WRITE | EV_ET | EV_PERSIST);
}

int main(int argc, char** argv)
{
    int port = 0;
    std::string ip = "127.0.0.1";
    for (int i = 0; i < argc; ++i)
    {
        if ( strcmp(argv[i], "-p") == 0 )
        {
            port = atoi(argv[i+1]);
        }
        else if ( strcmp(argv[i], "-t") == 0 )
        {
            ip = argv[i+1];
        }
    }

    if ( 0 == port )
    {
        showUsage();
        exit(0);
    }

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
    seraddr.sin_port = port;

    bind(listenFd, (sockaddr *)&seraddr, sizeof(seraddr));
    listen(listenFd, 10);

    //设置非阻塞
    int flags = fcntl(listenFd, F_GETFL, 0);
    if ( flags < 0 )
    {
        printf("socket error");
        return -1;
    }
    fcntl(listenFd, F_SETFL, flags | O_NONBLOCK);

    struct event_base *ev_base = event_base_new();
//    struct event ev;
//    event_set(&ev, listenFd, EV_READ | EV_PERSIST, NULL, NULL);
//
//    //struct event timer_ev;
//    struct timeval five;
//    memset(&five, 0, sizeof(five));
//    five.tv_sec = 5;
//    evtimer_set(&timer_ev, timer_cb, &timer_ev);
//    event_set(&timer_ev, -1, EV_TIMEOUT | EV_PERSIST, timer_cb, NULL);
//    event_add(&ev, NULL);
//    event_add(&timer_ev, &five);

    //循环
    event_base_dispatch(ev_base);

    return 0;
}
