#include <stdio.h> 
#include "websearch.h"
#include <iostream>

using namespace std;

int main()
{
	string topic;
	while(true){
		cout << "look up what you want: "; std::getline(std::cin,topic); 
		websearch *curl = new websearch(topic);
		cout << curl->getString() << endl;
		//return 2;
	}
}
