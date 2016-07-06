#ifndef __PB_RPC_CLEINT_H__
#define __PB_RPC_CLEINT_H__

#include "pbrpcdef.h"
#include "google/protobuf/service.h"

struct evrpc_pool;
struct evhttp_connection;

namespace pbrpc{

class CRPCChannel : public gpb::RpcChannel
{
public:
    CRPCChannel(CM::CReactor* reactor);
    ~CRPCChannel();

    virtual void CallMethod(const gpb::MethodDescriptor* methodDesc,
            gpb::RpcController* cotroller,
            const gpb::Message* req,
            gpb::Message* resp,
            gpb::Closure* done);

    bool AddServices(const std::string& ip, unsigned int port);

private:
    CM::CReactor* _reactor;
    evrpc_pool* _pool;
    std::vector<evhttp_connection*> _conns;
};

}

#endif
