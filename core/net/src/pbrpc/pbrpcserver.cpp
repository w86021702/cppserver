#include "pbrpcserver.h"

#include "google/protobuf/descriptor.h"
#include "google/protobuf/message.h"
#include "event2/rpc.h"
#include "httpserver.h"
#include "rpccontrol.h"

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
    _toDelete.clear();
}

int CRPCServer::RegisterServices(gpb::Service* services)
{
    const auto* servicesDesc = services->GetDescriptor();
    int methodCnt = servicesDesc->method_count();

    for ( int i = 0; i < methodCnt; ++i )
    {
        const auto* methodDesc = servicesDesc->method( i );
        auto* method = new RPCMethod();
        method->services = services;
        method->methodDesc = methodDesc;
        int ret = evrpc_register_generic(
                _rpcbase,
                methodDesc->full_name().c_str(),
                CRPCServer::InvokeMethod, method,
                //req部分
                CRPCControl::NewMsg,
                const_cast<gpb::Message*>(&services->GetRequestPrototype(methodDesc)),
                CRPCControl::DeleteMsg,
                CRPCControl::DeCodec,
                //resp部分
                CRPCControl::NewMsg,
                const_cast<gpb::Message*>(&services->GetResponsePrototype(methodDesc)),
                CRPCControl::DeleteMsg,
                CRPCControl::Complete,
                CRPCControl::Codec
                );

        if (ret != 0)
        {
            continue;
        }
        _toDelete.push_back(method);
    }

    return 0;
}

void CRPCServer::InvokeMethod(struct evrpc_req_generic* req, void* arg)
{
    const RPCMethod* rpc = static_cast<const RPCMethod*>(arg);
    rpc->services->CallMethod(
            rpc->methodDesc,
            NULL,
            static_cast<const gpb::Message*>(::evrpc_get_request(req)),
            static_cast<gpb::Message*>(::evrpc_get_reply(req)),
            gpb::NewCallback(&CRPCServer::DoneCallBack, req)
            );
}

void CRPCServer::DoneCallBack(struct evrpc_req_generic* req)
{
    evrpc_request_done(req);
}
