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
#include "myClock.h"
//typedef void(*)(void) function1;
commands::commands()
{
	heapsize = 21000000;
	load_init_size = 1; 
	festival_initialize(load_init_size, heapsize);
	festival_eval_command("(voice_en1_mbrola)");
	//time = myClock();
	setMap();
}

void commands::talk(std::string text)
{
	festival_say_text(EST_String(text.c_str()));
}

void commands::giveInfo(std::string question)
{	
	ifstream inFile2;
	EST_String newQuestion = EST_String(question.c_str());
	question = Personality::getKeyWords(question);
	std::string directory = "network/infoFiles/" + question + ".txt";
	inFile2.open(directory.c_str());
	std::string realInfo; //what the machine will say
	if(!inFile2)
	{
		websearch *curl = new websearch(question);
		std::cout << curl -> getString()<< std::endl;
		realInfo = curl->getString();
		 //need this to be ignored if not there
	}
	else
	{
		std::getline(inFile2,realInfo);
		std::cout << realInfo << std::endl;
	}
	talk(realInfo);
}

void commands::intro()
{
	ifstream inFile;
	inFile.open("txtFiles/userInfo.txt");
	if(!inFile)
	{
		talk("Hello User. I am JARVIS. What is your name?");
		std::string tempName;
		char* age = new char[3];
		cout << "Type your name: "; cin >> tempName;
		cout << "Type your age: "; cin >> age; 
		cout << "your name is " << tempName << endl;
		user newUser((char*)tempName.c_str(), age);
		newUser.storeInformation((char*)tempName.c_str(), age);
		talk("Hello " + tempName + ". How can I assist you?");
	}
	else
	{ 
		string name;
		std::getline(inFile, name);
		talk("Welcome back " + name + ". What do you need?");
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
	std::vector<std::string> svect;
	std::vector<std::string> saveVector;
	bool phrase = false; 
	for(std::map<std::vector<std::string>, mapTypes>::iterator it=keyWords.begin(); 
			it != keyWords.end(); it++)
	{
		svect = it->first; 
		//std::cout << svect.at(0) <<std::endl;
		for(int i=0; i < it->first.size();i++)
		{
			if(question.find(svect.at(i)) != -1)
			{
				phrase = true;
				saveVector = svect;  
			}
			else if(question.find(svect.at(i)) == -1)
			{
				phrase = false;
				saveVector.clear();
				break;
			}
		}
		if(phrase)//if phrase is still correct at end of loop it is a valid phrase;
		{
			chooseFunct(keyWords[saveVector], question);
			//(*this.*keyWords[saveVector].noFunction)();
			break;
		}
	}
	if(!phrase) //if at the end phrase is false
		talk("I do not understand your question. Please try again");
}

void commands::chooseFunct(mapTypes mapStruct, std::string question)
{
	if(mapStruct.noFunction!=NULL && mapStruct.strFunct != NULL)
		(*this.*mapStruct.strFunct)(question);
	else if(mapStruct.noFunction != NULL)
		(*this.*mapStruct.noFunction)();
	else if(mapStruct.strFunct != NULL)
		(*this.*mapStruct.strFunct)(question);
}
void commands::setAlarm()
{
	talk("what time sir?");
	int hour;
	int minute;
	std::cin >>  hour; 
	std::cin >>  minute; 
	time.setAlarm(hour, minute);
	talk("right away sir. your alarm is at" + std::to_string(hour) + std::to_string(minute));
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
		if(!myTunes.playMusic(keyword))
		{
			talk("sir, there seems to be an issue with finding the music folders");
		};
		//idle();
		//std::cout <<"does it get to end of plyamusic?" << std::endl;
 }

void commands::playMusic()
{
	talk("right away sir");
	myTunes.playMusic("");
}

void commands::stopMusic()
{
	myTunes.stopMusic();
}
void commands::setMap()
{
	std::vector<std::string> key(10);
	//void(commands::*value)(void);
	//(*this.*keyWords[test].noFunction)();
	//std::vector<std::string> test = {"test", "test"};
	//keyWords[vector<std::string>{"set", "alarm"}].noFunction = &commands::setAlarm;
	abstractMap({"set", "alarm"}, &commands::setAlarm);
	abstractMap({"play","music"}, &commands::playMusic);
	abstractMap({"stop","music"}, &commands::stopMusic);
	abstractMap({"meaning","life"}, &commands::meaningOfLife);
	abstractMapStr({"what"}, &commands::giveInfo);
	abstractMapStr({"who"}, &commands::giveInfo);
	abstractMapStr({"play", "music"}, &commands::playMusic);
	//abstractMap({"play","music"}, &commands::playMusic);
	//void(commands::*pointtest)(void) = keyWords[test].noFunction;	
}

void commands::abstractMap(vector<std::string> key, void(commands::*value)(void))
{
	keyWords[key].noFunction = value; 
}

void commands::abstractMapStr(vector<std::string> key, void(commands::*value)(std::string))
{
	keyWords[key].strFunct = value; 
}

void commands::meaningOfLife()
{
	talk("its 42");
	talk("DUMB SHIT");
}
