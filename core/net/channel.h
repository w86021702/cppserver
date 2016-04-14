#ifndef __CHANNEL_H__
#define __CHANNEL_H__

namespace COM{

class Channel
{
public:
	Channel();
	~Channel();

	virtual void HandleRead();
	virtual void HandleWrite();
	virtual void OnError();

private:
	int _fd;
};

}

#endif

