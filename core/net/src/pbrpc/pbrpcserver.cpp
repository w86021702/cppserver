#include "pbrpcserver.h"

#include "google/protobuf/descriptor.h"
#include "event2/rpc.h"
#include "httpserver.h"

using namespace pbrpc;

CRPCServer::CRPCServer(CM::CReactor * reactor, CHttpServer* http)
    :_reactor(reactor), _rpcbase(evrpc_init(http->GetHttp()))
{
}

CRPCServer::~CRPCServer()
{
    if (_rpcbase)
    {
        evrpc_free(_rpcbase);
    }

    for (const auto& method : _toDelete)
    {
        delete method;
    }
}

int CRPCServer::RegisterServices(gpb::Service* services)
{
    const auto* servicesDesc  = services->GetDescriptor();
    int methodCnt = servicesDesc->method_count();

    for ( int i = 0; i < methodCnt; ++i )
    {
        const auto* methodDesc = servicesDesc->method( i );
        auto* method = new RPCMethod();
        method->services = services;
        method->methodDesc = methodDesc;
        //evrpc_request_get_pool();
        _toDelete.push_back(method);
    }

    return 0;
}

int CRPCServer::InvokeMethod(struct evrpc_req_generic* req, void* arg)
{
    const RPCMethod* rpc = static_cast<const RPCMethod*>(arg);
    rpc->services->CallMethod(
            rpc->methodDesc,
            NULL,
            static_cast<const gpb::Message*>(::evrpc_get_request(req)),
            static_cast<gpb::Message*>(::evrpc_get_reply(req)),
            gpb::NewCallback(&CRPCServer::DoneCallBack, req)
            );
    

    return 0;
}

void CRPCServer::DoneCallBack(struct evrpc_req_generic* req)
{
}
