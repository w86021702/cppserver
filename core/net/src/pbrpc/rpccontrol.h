#ifndef __RPC_CONTROL_H__
#define __RPC_CONTROL_H__

#include "pbrpcdef.h"

struct evbuffer;
struct evrpc_req_generic;
struct evrpc_status;

namespace pbrpc{

class CRPCControl
{
public:
    CRPCControl();
    ~CRPCControl();

    static void Codec(evbuffer* ev, void* arg);
    static int DeCodec(void* arg, evbuffer* ev);

    static void DownCallBack(struct evrpc_req_generic* req);

    static void* NewMsg(void* arg);
    static void DeleteMsg(void* arg);
    static int Complete(void* arg);

    static void StatusCallBack(struct evrpc_status*, void*, void*, void*);

    //services->GetRequestPrototype(methodDesc).New(), NULL,
    //services->GetResponsePrototype(methodDesc).New(), NULL,
};

}

#endif
