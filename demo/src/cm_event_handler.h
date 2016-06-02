#ifndef __CM_EVENT_HANDLER_H__
#define __CM_EVENT_HANDLER_H__

namespace CM{

class EventHandler {
public:
    /**
     *      * 构造函数
     *           */
    EventHandler();

    /**
     *      * 析构函数
     *           */
    virtual ~EventHandler();

    /**
     *      * 获取socket句柄
     *           */
    virtual int getSocket() const = 0;

    /**
     *      * 获取reactor
     *           */
    //Reactor* getReactor() const;

    /**
     *      * 设置reactor
     *        */
    virtual void setReactor(void* reactor);

    /**
     *      * 处理读事件
     *           */
    virtual bool handleRead();

    /**
     *      * 处理写事件
     *           */
    virtual bool handleWrite();

    /**
     *      * 处理超时事件
     *           */
    virtual bool handleTimeout(unsigned int timerId);

    /**
     *      * 处理关闭事件
     *           * @return 是否delete此处理器
     *                */
    virtual bool handleClose() = 0;

    /**
     *      * 处理错误事件
     *           * @param events epoll事件
     *                * @param handler 出现错误的处理器
     *                     * @return 是否允许错误继续被其他处理器处理
     *                          */
    //virtual bool handleError(int events, EventHandler* handler);

    /**
     *      * 获取事件
     *           */
    int getEvents() const;

    /**
     *      * 设置事件
     *           */
    void setEvents(int events);

    /**
     *      * 设置超时
     *           * @param timeout 超时时间(毫秒)
     *                */
    unsigned int setTimer(int timeout);

    /**
     *      * 取消超时
     *           */
    void cancelTimer(unsigned int timerId);

protected:
    //Reactor* _reactor;
    int _events;
};

} //namespace cm

#endif
