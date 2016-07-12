#ifndef __LOG_MGR_H__
#define __LOG_MGR_H__

#include "commdef.h"

namespace CMLog{

enum ELogLevelType
{
    ELogDebug = 1,
    ELogInfo = 2,
    ELogErr = 3,
    ELogWarn = 4,
};

class CLogManager
{
public:
    static void Log(const std::string& msg);
    static void LogDebug(const std::string& msg); 
    static void Check(bool b, const std::string& msg);

};

#define LogDebug CLogManager::LogDebug

}


#endif
