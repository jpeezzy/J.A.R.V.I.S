#ifndef COMMANDS_H
#define COMMANDS_H

#include <EST_String.h>
#include <festival.h>
#include <iostream>
#include <map>
#include "music.h"
#include <mutex>
#include "myClock.h"
#include "network/websearch.h"
#include <thread>
#include <vector>
class commands{
	private:
		//typedef void(*function)(void) function1;
		//using func_t = void (*)(void);
		int heapsize;
		int load_init_size;
		myClock myTime;
		music myTunes;
		mutex _mutex;
		struct mapTypes
		{
			void(commands::*noFunction)(void)=NULL;
			void(commands::*strFunct)(std::string) = NULL;
		};
		std::map<std::vector<std::string>, mapTypes>  keyWords;
		std::thread clockThread;
		/*******************THESE METHODS DO WITH TIME/ALARM*/
		void showAlarmTime();
		void endAlarm();
		/**************************************/
		void setMap(); //sets map to proper values from txt file
		void setVector();//gets string from txt file and adds them to vector of stringi
		void abstractMap(vector<std::string> key, void(commands::*value)(void)); //abstracts adding values to map for programmer
		void abstractMapStr(vector<std::string> key, void(commands::*value)(std::string));
	public:
		commands(); //constructor, sets parameters and intializes festival voices
		void talk(std::string text);
		void giveInfo(std::string question); //gives information when asked
		void intro(); //goes when the user is new. asks for name/age
		//void converse(std::string input); //this if for WAY LATER;may depend on personality.  
		/***this is the function that grabs information from gui and stores the question so command can process*/
		bool checkQuestion();// checks to see if question is not duplicate
		void storeQuestion(std::string _question);
		std::string question;
		/////////////////////////////////////////////////////////////////////////////
		void idle(); //state where user inputs a question and then this calls task  
		void task(std::string question); // determines which task to do depending on input
		void chooseFunct(mapTypes mapStruct, std::string question);
		void setAlarm();
		void getTime();//gets time
		void playMusic(std::string music); // plays music (can either be genre or artist);
		void playMusic(); 
		void stopMusic(); //kills music
		void meaningOfLife();
};

#endif
