#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>
#include <sys/socket.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

struct event_base *g_base;
int create_client(struct event_base *ev_base, evutil_socket_t fd, struct bufferevent *bev);

int handleout(const char *req, size_t len);

void showUsage()
{
    printf("-t ip -p port\n");
}

void timer_cb(evutil_socket_t fd, short event, void* arg)
{
    printf("hello timer, %d\n", fd);
    struct event *ev = (struct event*)arg;
    struct timeval five;
    memset(&five, 0, sizeof(five));
    five.tv_sec = 1;
    event_add(ev, &five);
}

void on_accept(evutil_socket_t fd, short event, void *arg)
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
        struct bufferevent *bev;
        if ( 0 != create_client(g_base, newFd, bev) )
        {
            printf("make socket fail\n");
        }
    }
}

void on_read(evutil_socket_t fd, short event, void *arg)
{
    printf("on read\n");
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

void readcb(struct bufferevent *bev, void *ptr)
{
    printf("on read!buf:\n");
	struct evbuffer *input = bufferevent_get_input(bev);
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
		handleout(req+size, reqLen - size);

		//debug
		len = evbuffer_get_length(input);
		printf("after remove len:%d\n", len);
	}
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
    bufferevent_setcb(bev, readcb, NULL, NULL, NULL);
    bufferevent_enable(bev, EV_READ | EV_WRITE | EV_ET | EV_PERSIST);
}

int create_client(struct event_base *ev_base, evutil_socket_t fd, struct bufferevent *bev)
{
	bev = bufferevent_socket_new(ev_base, fd, BEV_OPT_CLOSE_ON_FREE);
    bufferevent_setcb(bev, readcb, NULL, NULL, NULL);
    bufferevent_enable(bev, EV_READ | EV_ET | EV_PERSIST);

	return 0;
}

int test(int argc, char** argv)
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
    printf("listen port %d\n", port);

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
    //struct event ev;
    //event_set(&ev, listenFd, EV_READ | EV_PERSIST, on_accept, NULL);
    struct event *listen_ev = event_new(ev_base, listenFd, EV_READ | EV_PERSIST | EV_ET, on_accept, NULL);
	g_base = ev_base;

    struct timeval five;
    memset(&five, 0, sizeof(five));
    five.tv_sec = 5;
    //evtimer_set(&timer_ev, timer_cb, &timer_ev);
    //event_set(&timer_ev, -1, EV_TIMEOUT | EV_PERSIST, timer_cb, NULL);
    //event_add(&timer_ev, &five);
    event_add(listen_ev, NULL);

    //循环
    //event_base_dispatch(ev_base); 没有事件时会退出
    event_base_loop(ev_base, 0x04);

    //event_free(listen_ev);
    //释放ev_base所有事件
    event_base_free(ev_base);

    return 0;
}

int handleout(const char *req, size_t len)
{
	printf("handle out req:%s, len:%u\n", req, len);
	return 0;
}

int main(int args, char** argv)
{
	test(args, argv);
	return 0;
}
