#include "test.pb.h"
#include "google/protobubf/RpcChannel.h"
#include "google/protobubf/Message.h"

class HelloClient : public google::protobuf::RpcChannel
{
public:
    void CallMethod(const ::google::protobuf::MethodDescriptor* method,  
            ::google::protobuf::RpcController* controller,  
            const ::google::protobuf::Message* request,  
            ::google::protobuf::Message* response,  
            ::google::protobuf::Closure* done)
    {  
 //           DataBufferOutputStream outputStream(...) // 取决于你使用的网络实现  
 //           request->SerializeToZeroCopyStream(&outputStream);  
 //       _connection->postData(outputStream.getData(), ...  
 //               ...  
    }  
};
