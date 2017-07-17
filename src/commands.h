#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <festival.h>
#include <EST_String.h>
#include "network/websearch.h"
#include "myClock.h"
#include <map>
#include <vector>
class commands{
	private:
		//typedef void(*function)(void) function1;
		//using func_t = void (*)(void); 
		int heapsize;
		int load_init_size;
		myClock time;
		struct mapTypes
		{
			void(commands::*noFunction)(void)=NULL;
		};
		std::map<std::vector<std::string>, mapTypes>  keyWords;
	public:
		commands(); //constructor, sets parameters and intializes festival voices
		void talk(std::string text);
		void giveInfo(std::string question); //gives information when asked
		void intro(); //goes when the user is new. asks for name/age
		//void converse(std::string input); //this if for WAY LATER;may depend on personality.  
		void idle(); //state where user inputs a question and then this calls task  
		void task(std::string question); // determines which task to do depending on input
		void setAlarm();
		void playMusic(std::string music); // plays music (can either be genre or artist);
		void stopMusic(); //kills music
};

#endif
