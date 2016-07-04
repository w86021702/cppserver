#include "httpserver.h"
#include "reactor.h"
#include "event2/http.h"

using namespace pbrpc;

void OnMessage(struct evhttp_request* req, void* arg);

CHttpServer::CHttpServer(CM::CReactor* reactor)
    : _httpd(NULL), _reactor(reactor)
{
    assert(reactor != NULL);
}

CHttpServer::~CHttpServer()
{
    if (_httpd)
    {
        evhttp_free(_httpd);
        _httpd = NULL;
    }
}

bool CHttpServer::Init(const unsigned int port)
{
    const std::string ip = "127.0.0.1";
    _httpd = evhttp_new((event_base*)_reactor->GetLoop());
    if (0 != evhttp_bind_socket(_httpd, ip.c_str(), port) )
    {
        printf("http server error!\n");
        return false;
    }
    evhttp_set_gencb(_httpd, OnMessage, NULL);

    return true;
}

void OnMessage(struct evhttp_request* req, void* arg)
{
    printf("on http msg\n");
}

evhttp* CHttpServer::GetHttp() const
{
    return _httpd;
}
