#ifndef MYCLOCK_H
#define MYCLOCK_H
#include <ctime>
#include <map>
#include "music.h"
class myClock
{
	private:
		time_t t;
		struct tm * now;
		int alarmHour;
		int alarmMinute;
		std::string alarmAP;
		bool alarmStart;
		std::map<int,std::string> converter;
		music alarmSound;
		std::map<int, std::string> alarmTime;
		/***these fucntions have to do with time and alarms */
		//void getAlarmTime();
		/******************/
	public:
		myClock();
		std::string getTime();
		std::string getDate();
		std::string getAlarmTime();
		bool checkAlarm();
		void setAlarm(int _alarmHour, int _alarmMinute, std::string AP);
		void waitAlarm();
		void startAlarm(); //possibly use bass audio or something
		void endAlarm(); // stops alarm
};


#endif 
