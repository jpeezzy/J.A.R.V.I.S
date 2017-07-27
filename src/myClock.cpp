#include "myClock.h"
#include <ctime>
#include <string>
#include <iostream>
#include <unistd.h>
#include "music.h"
#include <map>
#include <fstream>
#include <thread>
myClock::myClock()
{
	t = time(0);
	now = localtime(&t);
	usleep(1000);
	std::ifstream infile("txtFiles/converter.txt");
	int key;
	std::string value;
	while(infile >> key >> value)
		converter[key]=value;
}
std::string myClock::getTime()
{
	t = time(0);
	now = localtime(&t);
	std::string ap = "A. M";
	int hour = now->tm_hour;
	if(hour > 12)
	{
		hour=hour-12;
		ap = "P. M";
	}
	return (converter[hour] + ". " + converter[now->tm_min] + ". "+  ap);
	//return (std::to_string(now->tm_hour) + ":" + std::to_string(now->tm_min) + ":" +  std::to_string(now->tm_sec)); 
}

std::string myClock::getAlarmTime()
{
	std::cout <<  alarmHour << std::endl;
	return (converter[alarmHour] + ". " + converter[alarmMinute] + "." + alarmAP);
}

std::string numToWord(int x)
{
 
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
	return false; 
}
void myClock::setAlarm(int _alarmHour, int _alarmMinute, std::string AP)
{
	if(AP.compare("pm")==0)
	{
		alarmHour=_alarmHour+12;
	}
	else
		alarmHour=_alarmHour;
	alarmMinute = _alarmMinute;
	alarmAP = AP;
	waitAlarm();
}

void myClock::waitAlarm()
{
	while(!checkAlarm())
	{
		this->getTime();
		usleep(1000000);
	}
	startAlarm();
}

void myClock::startAlarm()
{
	if(alarmStart)
	{
		alarmSound.playMusic("");	
	}
}
void myClock::endAlarm()
{
	alarmSound.stopMusic();
	alarmStart = false;
}
