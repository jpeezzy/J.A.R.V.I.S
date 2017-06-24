#ifndef USER_H
#define USER_H
#include <fstream>
#include <iostream>
using namespace std;
class user
{
	private: 
		char* name; 
		char* age;

	public:
		//constructor setting default values i think
		user(char* name, char* age);
		void storeInformation(char* name, char* age); //stores information in txt file
};

#endif
