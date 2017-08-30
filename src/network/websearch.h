#ifndef WEBSEARCH_H
#define WEBSEARCH_H
#include <iostream>
#include "internet.h"

//#include <fstream>
class websearch : public internet
{
	private:
		std::string topic; //name of the topic (will need to append later);
		std::string topicHolder; //holds the information about a topic;
	public:
		websearch();
		websearch(std::string topicName); //constructor that creates and sends the information;
		void searchTopic(std::string topicName); //searches online for topic
		void storeInformation(std::string name, std::string information);//sotres information to txt file
		std::string cleanupInformation(std::string information); //cleans up the information string (removes tags etc)
		std::string getString(); //returns string s;
};
#endif
