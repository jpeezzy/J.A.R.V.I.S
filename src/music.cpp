#include "music.h"
#include <stdlib.h> 
#include <iostream>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <fstream>
bool music::playMusic(std::string FileName)
{
	//char *const fakearg[1] = {};
	//std::cout << (char*)FileName.c_str() << std::endl;
	FileName= std::string(getenv("HOME")) + "/Music/" + FileName + "/";
	char* const termArg[4] = {(char*)"gnome-terminal",  (char*)"--command", (char*)"cava", 0};
	char* const ARGS[5] = {(char*)"vlc",(char*)"-ZL", (char*)"--qt-start-minimized", (char*)FileName.c_str(), 0};
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
		execv("/usr/bin/gnome-terminal", termArg);
		//std::cout << "does parent process touch here at music?" <<std::endl;
		exit(EXIT_SUCCESS);
	}

	//https://stackoverflow.com/questions/10909011/how-to-use-fork-to-create-only-2-child-processes
	return true;
}

void music::stopMusic()
{
	pid_t parent_pid = getpid();
	kill(child1, SIGKILL); //child class 
	kill(child2, SIGKILL);
}
