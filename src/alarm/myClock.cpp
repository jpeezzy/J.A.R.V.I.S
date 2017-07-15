#include "myClock.h"
#include <ctime>
#include <string>
#include <iostream>

std::string myClock::getTime()
{
	t = time(0);
	now = localtime(&t);
	return (std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" +  std::to_string(now->tm_sec)); 
}

std::string myClock::getDate()
{

}

void myClock::setAlarm(int _alarmHour, int _alarmMinute)
{
	alarmHour=_alarmHour;
	alarmMinute = _alarmMinute;
}
myClock::myClock()
{
 t = time(0);
}

void myClock::startAlarm()
{

}

void myClock::endAlarm()
{

}
