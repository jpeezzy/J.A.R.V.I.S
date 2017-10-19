/* Welcome, this header file is designed to hvae the computer talk, depending on your operating system, different configuratiuons may be needed */
#ifndef SPEECH_H
#define SPEECH_H

#ifdef __linux__
#include <festival.h>
#include <EST_String.h>
#include <string>
#endif

#include <iostream>

class speech{
	private:
		int heapsize;
		int load_init_size;
	
	public:
		speech();
		void speak(std::string text); //enables speech
};



#endif
