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
#include "commands.h"
class client
{
	private:
		void error(const char *msg);
		void uploadFile(char* buffer, char* filename, int outputsocket);
		void recordVoice(); //you know this one
		void openSocket(int argc, char* argv[]); // trys to open socket
		void saveFile(char* buffer, int fd);
		void checkFormat(int argc, char* argv[]);
		void socketUpload();
		void socketExchange(); // talks to server and communicates how they recieve files;
		int sockfd, portno, n;
		struct sockaddr_in serv_addr;
		struct hostent *server;
		pid_t child1;
		int status=0;
		char buffer[256];
		std::string speechText;
		std::thread jarvisThread;
	public:
		client();
		commands jarvis;
		void socketConnect(int argc, char* argv[]);
		std::string getSpeechString();

};

#endif
