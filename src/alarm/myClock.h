#ifndef MYCLOCK_H
#define MYCLOCK_H
#include <ctime>
#include <iostream>
class myClock
{
	private:
		time_t t;
		struct tm * now;
		int alarmHour;
		int alarmMinute; 
	public:
		myClock();
		std::string getTime();
		std::string getDate();
		void setAlarm(int _alarmHour, int _alarmMinute);
		void startAlarm(); //possibly use bass audio or something
		void endAlarm(); // stops alarm 
};


#endif 
