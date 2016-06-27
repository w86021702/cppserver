#ifndef __CM_REQUEST_H__
#define __CM_REQUEST_H__

#include "commdef.h"

//namespace google
//{
//    namespace protobuf
//    {
//        class Message;
//    }
//}

namespace CM{

class CRequest
{
public:
    struct SHeader
    {
        unsigned int uid = 0;
        unsigned int cmd = 0;
        unsigned int version = 0; //版本号
        unsigned int dataLen = 0; //body长度
    };

public:
    CRequest();
    ~CRequest();

    bool Parse(const char *str, unsigned int len);

    void test();

private:
    SHeader _header;
    std::string _body;
};


}

#endif
