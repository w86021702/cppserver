#include "rpccontrol.h"
#include "event2/buffer.h"
#include "google/protobuf/message.h"
#include "google/protobuf/descriptor.h"

using namespace pbrpc;

void CRPCControl::Codec(evbuffer* ev, void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
}

int CRPCControl::DeCodec(void* arg, evbuffer* ev)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    return 0;
}

void CRPCControl::DownCallBack(struct evrpc_req_generic* req)
{
}

void* CRPCControl::NewMsg(void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    return (void*)msg->New();
}

void CRPCControl::CRPCControl::DeleteMsg(void* arg)
{
    gpb::Message* msg = static_cast<gpb::Message*>(arg);
    delete msg;
}

int CRPCControl::Complete(void* arg)
{
    return 0;
}

void CRPCControl::StatusCallBack(struct evrpc_status*, void*, void*, void*)
{}
