#include "cm_event_handler.h"

using namespace CM;

EventHandler::EventHandler(){}
EventHandler::~EventHandler(){}
bool EventHandler::handleRead(){ return false; }
bool EventHandler::handleWrite(){ return false; }
bool EventHandler::handleTimeout(unsigned int timerId){ return false; }

int EventHandler::getEvents() const
{
    return _events;
}

void EventHandler::setEvents(int events)
{
    _events |= events;
}

unsigned int EventHandler::setTimer(int timeout)
{
    return 0;
}

void EventHandler::cancelTimer(unsigned int timerId){}
void EventHandler::setReactor(void* reactor){}
