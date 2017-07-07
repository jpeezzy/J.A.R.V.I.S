#include "music.h"
#include <stdlib.h> 
#include <iostream>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
void music::playMusic(std::string FileName)
{
	//char *const fakearg[1] = {};
	std::cout << (char*)FileName.c_str() << std::endl;
	char* const termArg[6] = {"gnome-terminal",  "--command", "cava", 0};
	char* const ARGS[5] = {"vlc","-ZL", "--qt-start-minimized", (char*)FileName.c_str(), 0};
	pid_t pid = fork(); //to create a child process 
	//pid_t pid2 = fork();
		//exit(127);
	if (pid==0)
	{//child process
		std::cout <<"does it go here???" <<std::endl;
		execv("/usr/bin/vlc", ARGS);
		exit(127);
	}
	else
    { /* pid!=0; parent process */
		execv("/usr/bin/gnome-terminal", termArg);
	           waitpid(pid,0,0); /* wait for child to exit */
	}
	//system("vlc -ZL --qt-start-minimized ~/Music/MapleStory 2 BGM/");
}
