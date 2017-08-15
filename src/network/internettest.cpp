#include "internet.h"

int main()
{
	internet c;
	std::cout <<"type your words" << std::endl;
	std::string s;
	std::getline(std::cin, s); 
	c(s);
}
