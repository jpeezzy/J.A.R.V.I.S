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
	/*THIS CONVERTS NUMBERS TO STRINGS SO TTS CAN TALK */ 
	std::ifstream infile("txtFiles/converter.txt");
	int key;
	std::string value;
	while(infile >> key >> value)
		converter[key]=value;

	/* THIS GRABS ALL THE ALARM TIMES SET UP FROM TXT FILE */ 
	std::ifstream infile2("txtFiles/alarmTime.txt");
	while(infile2 >> key >> value)
		alarmTime[key] = value;
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

	for(std::map<int,std::string>::const_iterator it = alarmTime.begin(); it!= alarmTime.end(); it++)
	{
		std::cout<<(it->first)/100 << ":" << it->first%100 << " " << it->second << std::endl;
	}
	
	//std::cout <<"does it get to end of get Alarm time?" << std::endl;
	//std::cout <<  alarmHour << std::endl;
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
	for(std::map<int, std::string>::const_iterator it=alarmTime.begin(); it != alarmTime.end(); it++)
	{
		if(now->tm_hour == (it->first)/100)
		{
			if(now->tm_min == it->first%100)
			{
				return true; 
			}
		}
	}
/*	if(now->tm_hour == alarmHour)
	{
		if(now->tm_min == alarmMinute && !alarmStart)
		{
			return alarmStart =true; 
		}
	} */
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
	int tempTime = alarmHour*100 + alarmMinute;
	alarmTime[tempTime] = "1234567";
	std::ofstream outfile;
	outfile.open("txtFiles/alarmTime.txt", std::ofstream::out | std::ofstream::app);
	
	outfile << std::to_string(tempTime)<< " " << alarmTime[tempTime] <<std::endl;
	alarmAP = AP;
	outfile.close();
	//waitAlarm();
	return;
}

void myClock::waitAlarm()
{
	while(true)
	{
		if(alarmStart | !checkAlarm())
		{
			this->getTime();
			usleep(1000000);
			if(!checkAlarm())
			{
				alarmStart=false;
			}
		}
		else
		{
			startAlarm();
			alarmStart = true;
		}
	}
	//startAlarm();
}

void myClock::startAlarm()
{
		alarmSound.playMusic("");	
}

void myClock::endAlarm()
{
	alarmSound.stopMusic();
	//usleep(60000000);
}
