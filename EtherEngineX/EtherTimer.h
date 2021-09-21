#ifndef _TIMER_H_
#define _TIMER_H_

#include "EtherUtils.h"
#include "EtherModule.h"

class EtherTimer
{
public:
	EtherTimer();
};

class TimerModule : public EtherModule
{
public:
	static TimerModule& Instance();
	~TimerModule() {}

private:
	TimerModule();
};

#endif // !_TIMER_H_