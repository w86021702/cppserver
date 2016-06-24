#include "request.h"
#include "commdef.h"
//#include "google/protobuf/descriptor.h"
//#include "google/protobuf/message.h"
//#include "test.pb.h"

using namespace CM;
using namespace std;

bool CRequest::Parse(const char *str, unsigned int len)
{

    return true;
}

//template<class T>
//void testPbObj()
//{
//    const string typeName = T::descriptor()->full_name();
//    const google::protobuf::Descriptor * descriptor =
//        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(typeName);
//    cout << "descriptor: " << descriptor << endl;
//
//    const google::protobuf::Message* msg = 
//        google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
//
//    cout << "msg :" << msg->ShortDebugString() << endl;
//
//    T *obj = dynamic_cast<T*>(msg->New());
//    cout << "typeName:" << typeName << endl;
//    //obj->set_uid(11);
//    //obj->set_name("asdf");
//    
//    cout << "obj:" << obj->ShortDebugString() << endl;
//    delete obj;
//}

//void CRequest::test()
//{
//    testPbObj<hello::HelloWorldReq>();
//    testPbObj<hello::HelloWorldResp>();
//}
