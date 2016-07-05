#include "pbrpcclient.h"
#include "rpccontrol.h"
#include "reactor.h"
#include "rpc.pb.h"

using namespace CM;
using namespace pbrpc;
using namespace std;

void OnResp(test::EchoResp* resp)
{
    printf("resp: %s\n", resp->ShortDebugString().c_str());
    printf("msg: %s\n", resp->msg().c_str());
}

int main(int arg, char **argv)
{
    CReactor reactor;
    CRPCChannel channel(&reactor);
    channel.AddServices("127.0.0.1", 9096);
    test::TestSvr_Stub stub(&channel);

    CRPCControl contoller;
    test::EchoReq req;
    req.set_msg("hello rpc");
    test::EchoResp resp;
    stub.Echo(&contoller,&req, &resp, gpb::NewCallback(OnResp, &resp));

    reactor.OnLoop();

    return 0;
}
