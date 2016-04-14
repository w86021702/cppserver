#include "reactor.h"
#include <map>
#include <queue>


namespace CM{

class CReactor
{
public:
	CReactor();
	~CReactor();

private:
	std::map<unsigned int, CTimer> _timerMap;
	std::queue<CTimer> _timerHeap;

};

}
