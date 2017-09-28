//CLIENT SIDE that controls connection/ sockets, etc. 
#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h> //open()
#include <sys/stat.h> // open();
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/sendfile.h> //sendfile();
#include <sys/wait.h> /* for wait */

class client
{
	private:
		void error(const char *msg);
		void uploadFile(char* buffer, char* filename, int outputsocket);
		void recordVoice(); //you know this one
		void saveFile(char* buffer, int fd);
	public:
		client();


};

#endif
