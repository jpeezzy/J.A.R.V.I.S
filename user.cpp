#include <iostream>
#include "user.h"
#include <fstream>
using namespace std;
user::user(char* _name, char* _age){
	name = _name;
	age = _age;
}

void user::storeInformation(char* name, char* age)
{
	ofstream myfile("txtFiles/userInfo.txt");
	//myfile.open("userInfo.txt");
	myfile << name << "\n" << age;
	myfile.close();
}
