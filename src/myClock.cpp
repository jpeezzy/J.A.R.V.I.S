#include "myClock.h"
#include <ctime>
#include <string>
#include <iostream>
#include <unistd.h>
#include "music.h"
myClock::myClock()
{
		t = time(0);
		now = localtime(&t);
		usleep(1000);
}
std::string myClock::getTime()
{
	t = time(0);
	now = localtime(&t);
	return (std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" +  std::to_string(now->tm_sec)); 
}

std::string myClock::getDate()
{
	
}

bool myClock::checkAlarm()
{
	if(now->tm_hour == alarmHour)
	{
		if(now->tm_min == alarmMinute && !alarmStart)
		{
			return alarmStart =true; 
		}
	}
	//std::cout <<"does it return false?" << std::endl;
	return false; 
}
void myClock::setAlarm(int _alarmHour, int _alarmMinute)
{
	alarmHour=_alarmHour;
	alarmMinute = _alarmMinute;
}

void myClock::startAlarm()
{
	if(alarmStart)
	{
			music::playMusic("Alarm");	
			//alarmStart = false;
	}
}
void myClock::endAlarm()
{
	music::stopMusic();
	alarmStart = false;
}
