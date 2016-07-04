#include "pbrpcclient.h"
#include "rpccontrol.h"
#include "reactor.h"
#include "event2/rpc.h"
#include "event2/http.h"
#include "google/protobuf/descriptor.h"

using namespace pbrpc;

CRPCChannel::CRPCChannel(CM::CReactor* reactor)
    :_reactor(reactor), _pool(evrpc_pool_new((event_base*)_reactor->GetLoop()))
{
}

CRPCChannel::~CRPCChannel()
{
    for (auto& con : _conns)
    {
        evrpc_pool_remove_connection(_pool, con);
        evhttp_connection_free(con);
    }

    evrpc_pool_free(_pool);
}

void CRPCChannel::CallMethod(const gpb::MethodDescriptor* methodDesc,
        gpb::RpcController* cotroller,
        const gpb::Message* req,
        gpb::Message* resp,
        gpb::Closure* done)
{
    int ret = evrpc_send_request_generic(
            _pool,
            const_cast<gpb::Message*>(req),
            resp,
            CRPCControl::StatusCallBack,
            done,
            methodDesc->full_name().c_str(),
            CRPCControl::Codec,
            CRPCControl::DeleteMsg,
            CRPCControl::DeCodec
            );

    if (0 != ret)
    {
        //core
        printf("%s fail\n", __func__);
    }
}

int CRPCChannel::AddServices(const std::string& ip, unsigned int port)
{
    struct evhttp_connection* con = evhttp_connection_base_new(NULL, NULL, ip.c_str(), port);
    evrpc_pool_add_connection(_pool, con);
    _conns.push_back(con);

    return 0;
}
