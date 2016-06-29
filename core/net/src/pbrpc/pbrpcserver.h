#ifndef __PB_RPC_SVR__
#define __PB_RPC_SVR__

#include "pbrpcdef.h"
#include "google/protobuf/service.h"

namespace pbrpc
{

class CRPCServer
{
public:
    CRPCServer();
    ~CRPCServer();

    int RegisterServices(gdb::Service* services);

private:


};


}
#endif
