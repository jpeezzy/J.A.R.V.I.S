//COMMAND CLASS, TELLS THE AI WHAT TO DO 

#include "commands.h" 
#include <iostream>
#include <fstream>
#include <festival.h> 
#include <EST_String.h>
#include "user.h"
#include "Personality.h"
#include "music.h"
#include <algorithm>
#include <ctype.h>
#include "network/websearch.h"
commands::commands()
{
	heapsize = 21000000;
	load_init_size = 1; 
	festival_initialize(load_init_size, heapsize);
	festival_eval_command("(voice_kal_diphone)");
}

void commands::talk(EST_String text)
{
	festival_say_text(text);
}

void commands::giveInfo(std::string question)
{	
	ifstream inFile2;
	EST_String newQuestion = EST_String(question.c_str());
	question = Personality::getKeyWords(question);
	std::string directory = "network/infoFiles/" + question + ".txt";
	inFile2.open(directory.c_str());
	EST_String realInfo; //what the machine will say
	if(!inFile2)
	{
		websearch *curl = new websearch(question);
		std::cout << curl -> getString()<< std::endl;
		realInfo = EST_String(curl->getString().c_str());
		 //need this to be ignored if not there
	}
	else
	{
		std::string information;
		std::getline(inFile2,information);
		std::cout << information << std::endl;
		realInfo = EST_String(information.c_str());
	}
	//std::cout << realInfo << std::endl;
	talk(realInfo);
}

void commands::intro()
{
	ifstream inFile;
	inFile.open("txtFiles/userInfo.txt");
	if(!inFile)
	{
		festival_say_text("Hello User. I am JARVIS. What is your name?");
		char* tempname = new char[20];
		char* age = new char[3];
		cout << "Type your name: "; cin >> tempname;
		cout << "Type your age: "; cin >> age; 
		cout << "your name is " << tempname << endl;
		user newUser(tempname, age);
		newUser.storeInformation(tempname, age);
		EST_String name = EST_String(tempname);
		festival_say_text("Hello " + name + ". How can I assist you?");
	}
	else
	{ 
		string name;
		std::getline(inFile, name);
		char* tempName = new char[35];
		std::strcpy(tempName, name.c_str());
		EST_String realName = EST_String(tempName);
		cout << realName << endl;
		festival_say_text("Welcome back " + realName + ". What do you need?");
	}
	idle();
}

void commands::idle() 
{
	std::string question; 
	while(true)
	{
		ifstream inFile2;
		cout <<"Ask me a Question: ";getline(cin,question);
		EST_String newQuestion = EST_String(question.c_str());
	//festival_say_text("I do not understand your question:. " + newQuestion + ". Would you like me to google it?");
	//cout << "y/n?"; cin >> ans;
		task(question);
	}
}

void commands::task(std::string question)
{
	if((question.find("play") != -1 & question.find("music") != -1))
	{
		playMusic(question);
	}
	else if((question.find("who") !=-1) || (question.find("what") != -1))
	{
		giveInfo(question);
	}
}

 void commands::playMusic(std::string question)
 {
	 //e.g. string format: play some classical music. music is at the end, play is first
//http://id3lib.sourceforge.net/ may use this later to actually get metadata. 
		std::string keyword = question; //foflder to search for music
		try{
		keyword.erase(keyword.find("play"), 4);	
		//std::cout << keyword << std::endl;
		keyword.erase(keyword.find("music"),5); 
		//std::cout << keyword << std::endl;
		keyword.erase(std::remove_if(keyword.begin(),keyword.end(), ::isspace), keyword.end());
		keyword.erase(keyword.find("some"),4);
		//std::cout << keyword << std::endl;
		}catch(std::out_of_range e){std::cout <<"error at try" << std::endl;}// folder to search stuff in; 
		//play some music
		talk("Right away sir");
		if(!music::playMusic(keyword))
		{
			talk("sir, there seems to be an issue with finding the music folders");
		};
		//idle();
		std::cout <<"does it get to end of plyamusic?" << std::endl;
 }	
	//std::cout << "gets to task" << std::endl;
