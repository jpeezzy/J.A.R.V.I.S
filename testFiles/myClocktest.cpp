#include "myClock.h"
#include <iostream>
#include <unistd.h>
int main()
{	
	myClock c; 
	c.setAlarm(8, 30);
	while(true)
	{
	std::cout<< c.getTime() << std::endl;

	if(c.checkAlarm())
	{
		c.startAlarm();
	}
	usleep(1000000);

	}
	return 0;
}
