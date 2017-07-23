#ifndef MYCLOCK_H
#define MYCLOCK_H
#include <ctime>
#include <iostream>
#include <map>
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
		void waitAlarm();
	public:
		myClock();
		std::string getTime();
		std::string getDate();
		bool checkAlarm();
		void setAlarm(int _alarmHour, int _alarmMinute, std::string AP);
		void startAlarm(); //possibly use bass audio or something
		void endAlarm(); // stops alarm
};


#endif 
