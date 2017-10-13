#include "music.h"
#include <stdlib.h> 
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <fstream>

#ifndef __MACH
#include <signal.h>
#endif
bool music::playMusic(std::string FileName)
{
	//char *const fakearg[1] = {};
	//std::cout << (char*)FileName.c_str() << std::endl;
	#ifdef __MACH__
		child1 = fork();
		if(child1)
		{
		}
		else
		{
		char* const termArg[5] = {(char*)"osascript",(char*) "iTunes.scpt"};
		execv("/usr/bin/osascript", termArg);
		return true;
		}
	#endif

	#ifdef __unix
	FileName= std::string(getenv("HOME")) + "/Music/" + FileName + "/";
	//char* const termArg[4] = {(char*)"gnome-terminal",  (char*)"--command", (char*)"cava", 0};
	char* const termArg[9] = {(char*)"urxvt", (char*)"-geometry", (char*) "500x500", (char*)"-depth", (char*)"32", (char*)"-bg",(char*) "rgba:0000/0000/0001/cccc", (char*)"-e", (char*)"cava" };
	char* const ARGS[6] = {(char*)"vlc",(char*)"-ZL", (char*)"--qt-start-minimized", (char*)FileName.c_str(), (char*)"--quiet", 0};
	std::cout << FileName << std::endl;
	
	std::ifstream inFile; inFile.open(FileName.c_str());
	if(!inFile)
		return false; //if it can't find the file;

	child1=fork();
	if(child1)
	{
		child2=fork();
		if(child2)
		{
		}
		else
		{
			std::cout <<"does it launch vlc???" <<std::endl;
			execv("/usr/bin/vlc", ARGS);
			//execv("/usr/bin/gnome-terminal", termArg);
			exit(EXIT_SUCCESS);
		}
	}
	else
	{
		execv("/usr/bin/urxvt", termArg);
		//std::cout << "does parent process touch here at music?" <<std::endl;
		exit(EXIT_SUCCESS);
	}

	//https://stackoverflow.com/questions/10909011/how-to-use-fork-to-create-only-2-child-processes
	#endif
	return true;
}

void music::stopMusic()
{
	pid_t parent_pid = getpid();
	kill(child1, SIGKILL); //child class 
	kill(child2, SIGKILL);
}
