#include "rpccontrol.h"

#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

#include <sys/queue.h>
#include "event2/buffer.h"
#include "event2/event.h"
#include "event2/rpc.h"
#include "event2/rpc_struct.h"
#include "event2/http.h"
#include "logmgr.h"

using namespace pbrpc;
using namespace std;

void CRPCControl::Codec(evbuffer* ev, void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    //CM::LogDebug("codec:" + msg->GetTypeName());
    char buffer[MAX_BUFF_SIZE];
    if (!msg->SerializeToArray(buffer, MAX_BUFF_SIZE))
    {
        CM::LogDebug("CRPCControl::Codec:" + msg->ShortDebugString());
    }

    evbuffer_add(ev, buffer, MAX_BUFF_SIZE);
}

int CRPCControl::DeCodec(void* arg, evbuffer* ev)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    //CM::LogDebug("decode:" + msg->GetTypeName());
    char buffer[MAX_BUFF_SIZE];
    evbuffer_remove(ev, buffer, MAX_BUFF_SIZE);
    if ( !msg->ParseFromArray(buffer, MAX_BUFF_SIZE) )
    {
        CM::LogDebug("decode fail:" + msg->GetTypeName());
        return -1;
    }

    CM::LogDebug("decode success:" + msg->ShortDebugString());
    return 0;
}

void CRPCControl::DownCallBack(struct evrpc_req_generic* req)
{
    //CM::LogDebug(req->uri());
    //struct evbuffer* ev = evbuffer_new();
    //evbuffer_add(ev, "hello\r\n", 7);
    //evhttp_send_reply(req, 200, "OK", ev);
    //evbuffer_free(ev);
}

void* CRPCControl::NewMsg(void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    CM::LogDebug("on new msg:" + msg->GetTypeName());
    return (void*)msg->New();
}

void CRPCControl::CRPCControl::DeleteMsg(void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    CM::LogDebug("delete msg:" + msg->GetTypeName());
    delete msg;
}

void CRPCControl::CRPCControl::Clear(void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    CM::LogDebug("clear msg:" + msg->GetTypeName());
}

int CRPCControl::Complete(void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    CM::LogDebug("complete:" + msg->GetTypeName());
    
    return 0;
}

void CRPCControl::StatusCallBack(struct evrpc_status* status, void*, void*, void* arg)
{
    if (status->error != EVRPC_STATUS_ERR_NONE) 
    {
        CM::LogDebug("CRPCControl::StatusCallBack fail!");
        return ;
    }

    gpb::Closure* done = static_cast<gpb::Closure*>(arg);
    done->Run();
}
