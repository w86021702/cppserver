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
    if (!msg->IsInitialized())
    {
        CM::LogDebug("CRPCControl::Codec fail:" + msg->ShortDebugString());
        return ;
    }

    //CM::LogDebug("codec:" + msg->GetTypeName());
    string ss = msg->SerializeAsString();
    assert(ss.size() < MAX_BUFF_SIZE);
    evbuffer_add(ev, ss.c_str(), ss.size());
}

int CRPCControl::DeCodec(void* arg, evbuffer* ev)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    //CM::LogDebug("decode:" + msg->GetTypeName());
    char buffer[MAX_BUFF_SIZE];
    int buflen = evbuffer_get_length(ev);
    assert(MAX_BUFF_SIZE > buflen);
    int len = evbuffer_remove(ev, buffer, buflen);
    if (len == 0)
    {
        CM::LogDebug("len == 0, decode fail:" + msg->GetTypeName());
        return -1;
    }

    printf("len:%d, buflen:%d, %s\n", len, buflen, buffer);

    if ( !msg->ParseFromArray(buffer, buflen) )
    {
        CM::LogDebug("decode fail:" + msg->GetTypeName());
        return -1;
    }

    CM::LogDebug("decode success:" + msg->ShortDebugString());
    return 0;
}

void CRPCControl::DownCallBack(struct evrpc_req_generic* req)
{
    CM::LogDebug("DownCallBack msg:");
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
    //delete msg;
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

        //if (status->error == EVRPC_STATUS_ERR_HTTP)
        //{
        //}
        return ;
    }

    gpb::Closure* done = static_cast<gpb::Closure*>(arg);
    done->Run();
}
