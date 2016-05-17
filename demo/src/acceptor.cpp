#include "acceptor.h"
#include "event2/util.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/bufferevent.h"
#include <assert.h>
#include <string.h>
#include "client.h"
#include "reactor.h"

using namespace CM;

void acceptor_readcb(evutil_socket_t fd, short event, void *arg);
void acceptor_writecb(struct bufferevent *bev, void *ptr);
void acceptor_eventcb(struct bufferevent *bev, short event, void *arg);

CAcceptor::CAcceptor(struct event_base *ev_base, int fd, unsigned int port)
    : CChannel(fd), _ev_base(ev_base), _port(port)
{
    assert(ev_base != NULL && fd > 0);

    sockaddr_in seraddr;
    memset(&seraddr, 0, sizeof(seraddr));
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(port);

    if ( 0 != evutil_make_socket_nonblocking(_fd) )
    {
        printf("socket error\n");
        return ;
    }

    if ( bind(_fd, (sockaddr *)&seraddr, sizeof(seraddr)) < 0 )
    {
        printf("bind fail\n");
        return ;
    }

    if ( listen(_fd, 10) < 0 )
    {
        printf("listen fail\n");
        return ;
    }

    _listen_ev = event_new(ev_base, _fd, EV_READ | EV_PERSIST | EV_ET, acceptor_readcb, this);
    printf("listen %d\n", _fd);
}

CAcceptor::~CAcceptor()
{
	if (_listen_ev)
		event_free(_listen_ev);
}

int CAcceptor::HandleRead()
{
    printf("on accept\n");
    struct sockaddr_in addr;
    socklen_t len = 0;
    while (1)
    {
        evutil_socket_t newFd = accept(_fd, (struct sockaddr*)&addr, &len);
        if (newFd <= 0)
        {
            break;
        }

        printf("accept create new_bufferev fd:%d\n", newFd);
        auto* channel = new CClient(_ev_base, newFd);
    }
    return 0;
}

int CAcceptor::HandleWrite()
{
    return 0;
}

void CAcceptor::OnError()
{
}

int CAcceptor::HandleOut(char* buf, unsigned int len)
{
	printf("###recv:%s, %u\n", buf, len);
	//解析协议
	return 0;
}

int CAcceptor::GetSocketFd()
{
	return _fd;
}

int CAcceptor::HandleClose()
{
    //delete this;
    return 0;
}

void acceptor_readcb(evutil_socket_t fd, short event, void *arg)
{
    CChannel *channel = (CChannel*)arg;
	int ret = channel->HandleRead();
    if (ret != 0)
    {
        return ;
    }

}

void* CAcceptor::GetReactor() const
{
    return _ev_base;
}

int CAcceptor::SetReactor(void* reactor)
{
	CReactor* rea = (CReactor *) reactor;
	_ev_base = (event_base*)rea->GetReactor();
	event_base_set(_ev_base, _listen_ev); 
    event_add(_listen_ev, NULL);
    return 0;
}

void acceptor_writecb(struct bufferevent *bev, void *ptr)
{
}

void acceptor_eventcb(struct bufferevent *bev, short event, void *arg)
{
	if (event & BEV_EVENT_EOF)
		printf("connection closed\n");
	else if (event & BEV_EVENT_ERROR)
		printf("some other error\n");

	//这将自动close套接字和free读写缓冲区
	//bufferevent_free(bev);
	delete (CAcceptor *)arg;
}

////////////////////////////////////////////////////////////////////

