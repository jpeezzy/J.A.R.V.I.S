#ifndef WEBSEARCH_H
#define WEBSEARCH_H
#include <iostream>
//#include <fstream>
class websearch
{
	private:
		std::string topic; //name of the topic (will need to append later);
		std::string s; //holds the information about a topic;	
	public:
		websearch(std::string topicName); //constructor that creates and sends the information;
		void storeInformation(std::string name, std::string information);//sotres information to txt file
		std::string cleanupInformation(std::string information); //cleans up the information string (removes tags etc)
		std::string getString(); //returns string s;
};
#endif
