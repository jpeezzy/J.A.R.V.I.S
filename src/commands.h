#ifndef COMMANDS_H
#define COMMANDS_H

#include <iostream>
#include <festival.h>
#include <EST_String.h> 
class commands{
	private:
		int heapsize;
		int load_init_size;
	public:
		commands(); //constructor, sets parameters and intializes festival voices
		void talk(EST_String text);
		void giveInfo(std::string question); //gives information when asked
		void playMusic(std::string music); // plays music when you say so (can either be genre or artist);
		void converse(std::string input); //this if for WAY LATER; 
};

#endif
