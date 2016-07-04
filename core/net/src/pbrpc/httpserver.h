#ifndef __HTTP_SERVER_H__
#define __HTTP_SERVER_H__

#include "pbrpcdef.h"

namespace CM{
    class CReactor;
}

struct evhttp;

namespace pbrpc
{

class CHttpServer
{
public:
    CHttpServer(CM::CReactor* reactor);
    ~CHttpServer();

    bool Init(const unsigned int port);
    
    evhttp* GetHttp() const;

private:
    CM::CReactor* _reactor;
    struct evhttp* _httpd;
};

}



#endif
