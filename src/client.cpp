#include "client.h"
#include <iostream>
#include "commands.h"


//for sleep
#include <chrono>
client::client()
{
	jarvisThread = std::thread(&commands::intro, &jarvis);
}
void client::error(const char *msg)
{
	perror(msg);
	exit(0);
}

void client::recordVoice()
{
	std::cout <<"RECORDING FILE NOW" << std::endl;
	char* const args[11] = {(char*)"rec", (char*)"-r", (char*)"16000", (char*)"-c", (char*)"1", (char*)"-d", (char*)"output.wav", (char*)"trim", (char*)"0", (char*)"5", 0};
	execv("/usr/bin/sox", args);
}

void client::uploadFile(char* buffer, char* filename, int output_socket)
{
//x230	
//char* server = "masa@192.168.0.114:/home/masa/wavfiles";
//t60
	char* server = (char*)"ieee@10.0.0.69:/home/ieee/server/";
	//char* server = (char*)"masa@192.168.29.119:/home/masa/jarvis/server/server";
//	char sshLong[200] = "ssh -p "; //x230
	char sshLong[200] = "ssh -p "; //cluster
	char* port = (char*)"1337"; //cluster
//	char* port = (char*)""; //t60
	printf("ssh: %s", sshLong);
	strcat(sshLong, port);
	printf("ssh: %s", sshLong);
	char* sshcont = (char*)" -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null/";
	strcat(sshLong, sshcont);
	printf("ssh: %s", sshLong);
	char* args[8] = {(char*)"rsync", (char*)"-avz", (char*)"-e", (char*)sshLong, (char*)"--progress", (char*)filename, (char*)server, 0};
	execv("/usr/bin/rsync", args);
}

void client::checkFormat(int argc, char* argv[])
{
	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}
}

void client::socketConnect(int argc, char* argv[])
{
	checkFormat(argc, argv);
	child1 = fork();
	if(child1)
	{
		printf("");
		wait(&status);
	}
	else
		recordVoice();
	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	openSocket(argc, argv);
	socketUpload();
	socketExchange();
}

void client::openSocket(int argc, char* argv[])
{
	///////////////////////////////////////////////////////////////////////
	//ERROR CHCEKING IN THIS BLOCK//
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	///////////////////////////////////
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");
}

void client::socketUpload() //uploads file
{
	pid_t child2, wpid;
	int status2 =0;		
	child2 = fork();
	if(child2)
	{
		printf("\n");
		wait(&status2);
	}
	else
	{
		uploadFile(buffer, (char*)"output.wav", sockfd);
		exit(0);
	}
	while((wpid = wait(&status2)) > 0);

}
int main(int argc, char *argv[])
{
	client c;
	//commands command;
	c.socketConnect(argc, argv);
	//command.task(c.getSpeechString());
	c.jarvis.storeQuestion(c.getSpeechString());
	//std::this_thread::sleep_for (std::chrono::seconds(10));	
	while(1)
	{
		
	}
	return 0;
}

std::string client::getSpeechString()
{
	return speechText;
}

void client::socketExchange()
{
	bzero(buffer,256);
	//	fgets(buffer,255,stdin);
	strncpy(buffer, "sent file", 9);
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0) 
		error("ERROR writing to socket");

	bzero(buffer,256);
	//Once sent message, wait for response from server
	while(n = read(sockfd,buffer,256) & strcmp(buffer, "jarvis says") != 0 ){}
	n = write(sockfd, "ready", strlen(buffer));
	printf("%s \n",buffer);
	bzero(buffer,256);
	n = read(sockfd,buffer,256);
	//SEND To the front end of computer;
	char* phrase  = buffer;
	speechText = std::string(phrase);
	printf("%s \n", phrase);
//	printf("%s \n",buffer);
	if (n < 0) 
		error("ERROR reading from socket");

	//int input_file = open("sample.wav", O_RDONLY); //OPESN FILE
	//	printf("this is what the buffer says: %d \n", buffer);
	close(sockfd);
}

