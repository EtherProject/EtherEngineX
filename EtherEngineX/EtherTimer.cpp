#include "EtherTimer.h"

TimerModule& TimerModule::Instance()
{
	static TimerModule* _instance = new TimerModule();
	return *_instance;
}

TimerModule::TimerModule()
{

}