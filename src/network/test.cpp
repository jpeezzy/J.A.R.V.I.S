#include <stdio.h> 
#include "websearch.h"
#include <iostream>

using namespace std;

int main()
{
	websearch *curl = new websearch();	
	string topic;
	while(true){
		cout << "look up what you want: "; std::getline(std::cin,topic); 
		curl->searchTopic(topic);
		cout << curl->getString() << endl;
		//return 2;
	}
}
