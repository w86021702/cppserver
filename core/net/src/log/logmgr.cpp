#include "logmgr.h"

using namespace CM;
using namespace std;

void CLogManager::Log(const string& msg)
{
    printf("error: %s\n", msg.c_str());
}

void CLogManager::Check(bool b, const string& msg)
{
    if (b)
    {
        printf("error: %s\n", msg.c_str());
    }
}

void CLogManager::LogDebug(const std::string& msg)
{
    printf("debug : %s\n", msg.c_str());
}
