#ifndef __RPC_CONTROL_H__
#define __RPC_CONTROL_H__

#include "pbrpcdef.h"
#include "google/protobuf/service.h"

struct evbuffer;
struct evrpc_req_generic;
struct evrpc_status;

namespace pbrpc{

class CRPCControl : public gpb::RpcController
{
public:
    CRPCControl(){};
    virtual ~CRPCControl(){};

    // Client-side methods ---------------------------------------------
    // These calls may be made from the client side only.  Their results
    // are undefined on the server side (may crash).

    // Resets the RpcController to its initial state so that it may be reused in
    // a new call.  Must not be called while an RPC is in progress.
    virtual void Reset() {}

    // After a call has finished, returns true if the call failed.  The possible
    // reasons for failure depend on the RPC implementation.  Failed() must not
    // be called before a call has finished.  If Failed() returns true, the
    // contents of the response message are undefined.
    virtual bool Failed() const { return !_reason.empty(); }

    // If Failed() is true, returns a human-readable description of the error.
    virtual std::string ErrorText() const { return _reason; }

    // Advises the RPC system that the caller desires that the RPC call be
    // canceled.  The RPC system may cancel it immediately, may wait awhile and
    // then cancel it, or may not even cancel the call at all.  If the call is
    // canceled, the "done" callback will still be called and the RpcController
    // will indicate that the call failed at that time.
    virtual void StartCancel() {}

    // Server-side methods ---------------------------------------------
    // These calls may be made from the server side only.  Their results
    // are undefined on the client side (may crash).

    // Causes Failed() to return true on the client side.  "reason" will be
    // incorporated into the message returned by ErrorText().  If you find
    // you need to return machine-readable information about failures, you
    // should incorporate it into your response protocol buffer and should
    // NOT call SetFailed().
    virtual void SetFailed(const std::string& reason)
    {
        _reason = reason;
    }

    // If true, indicates that the client canceled the RPC, so the server may
    // as well give up on replying to it.  The server should still call the
    // final "done" callback.
    virtual bool IsCanceled() const { return false; }

    // Asks that the given callback be called when the RPC is canceled.  The
    // callback will always be called exactly once.  If the RPC completes without
    // being canceled, the callback will be called after completion.  If the RPC
    // has already been canceled when NotifyOnCancel() is called, the callback
    // will be called immediately.
    //
    // NotifyOnCancel() must be called no more than once per request.
    virtual void NotifyOnCancel(gpb::Closure* callback) {}

    static void Codec(evbuffer* ev, void* arg);
    static int DeCodec(void* arg, evbuffer* ev);

    static void DownCallBack(struct evrpc_req_generic* req);

    static void* NewMsg(void* arg);
    static void DeleteMsg(void* arg);
    //解密失败时调用
    static void Clear(void* arg);
    static int Complete(void* arg);

    static void StatusCallBack(struct evrpc_status*, void*, void*, void*);

    //services->GetRequestPrototype(methodDesc).New(), NULL,
    //services->GetResponsePrototype(methodDesc).New(), NULL,
private:
    std::string _reason;
};

}

#endif
