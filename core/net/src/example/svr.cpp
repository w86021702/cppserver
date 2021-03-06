#include "pbrpcserver.h"
#include "httpserver.h"
#include "reactor.h"
#include "rpc.pb.h"

using namespace CM;
using namespace std;

class Impl : public test::TestSvr
{
public:
  virtual void Echo(::google::protobuf::RpcController* controller,
                       const ::test::EchoReq* request,
                       ::test::EchoResp* response,
                       ::google::protobuf::Closure* done)
  {
      while(1) {}
      string ss = "echo:hello! req : " + request->msg();
      response->set_msg(ss);
      response->set_code(99);
      done->Run();
  }

  virtual void Echo2(::google::protobuf::RpcController* controller,
                       const ::test::EchoReq* request,
                       ::test::EchoResp* response,
                       ::google::protobuf::Closure* done)
  {
      string ss = "echo2: hi! req : " + request->msg();
      response->set_msg(ss);
      response->set_code(2);
      done->Run();
  }
};


int main(int args, char **argv)
{
    CReactor reactor;
    pbrpc::CHttpServer httpSvr(&reactor);
    httpSvr.Init(9096);
    pbrpc::CRPCServer rpcSvr(&reactor, &httpSvr);
    Impl impl;
    rpcSvr.RegisterServices(&impl);

    reactor.OnLoop();
    return 0;
}
