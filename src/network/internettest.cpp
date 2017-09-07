#include "internet.h"

int main()
{
	internet c;
	//std::cout <<"type your words" << std::endl;
	std::string s;
	//std::getline(std::cin, s); 
	//c(s);
	//std::cout << c.getText("http://api.openweathermap.org/data/2.5/weather?q=Los%20Angeles&appid=13098574849c3ecded8a4fc7d0e2ab4c&units=imperial") << std::endl;
	std::cout << c.getLocation() <<std::endl;
}
