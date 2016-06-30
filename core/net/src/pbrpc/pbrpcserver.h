#ifndef __PB_RPC_SVR__
#define __PB_RPC_SVR__

#include "pbrpcdef.h"
#include "google/protobuf/service.h"

namespace CM
{
struct CReactor;
}

struct evrpc_base;
struct evrpc_req_generic;

namespace pbrpc
{
struct CHttpServer;

class CRPCServer
{
public:
    CRPCServer(CM::CReactor * reactor, CHttpServer* http);
    ~CRPCServer();

    int RegisterServices(gpb::Service* services);

    int InvokeMethod(struct evrpc_req_generic* req, void* arg);

    static void DoneCallBack(struct evrpc_req_generic* req);

private:
    struct RPCMethod
    {
        gpb::Service* services;
        const gpb::MethodDescriptor* methodDesc;
    };

private:
    CM::CReactor* _reactor;
    evrpc_base* _rpcbase;
    std::map<unsigned int, RPCMethod> _methods;
    std::vector<RPCMethod*> _toDelete;

};


}
#endif
