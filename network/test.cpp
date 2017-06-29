#include <stdio.h> 
#include "websearch.h"
#include <iostream>

using namespace std;

int main()
{
	websearch *curl = new websearch("the last airbender");
	cout << curl->getString() <<endl;
	return 2;
}
