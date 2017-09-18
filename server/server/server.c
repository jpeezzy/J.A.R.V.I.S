/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h> //for open();
#include <sys/wait.h> //wait();
void error(const char *msg)
{
	perror(msg);
	exit(1);
}

void saveFile(char* buffer, int fd); //saves buffer arrya to file

char* speechToText(char* filename); //analyzes wav file using cmusphinx

int main(int argc, char *argv[])
{
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	int buffer_size = 256;
	char buffer[buffer_size];
	struct sockaddr_in serv_addr, cli_addr;
	ssize_t n;

	//ERROR CHECKING ////////////////
	if (argc < 2) {
		fprintf(stderr,"ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //this is the socket i believe
	if (sockfd < 0) 
		error("ERROR opening socket");
	////////////////////////////////////
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	/////////////ERROR ON BINDING///////
	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	////////////////////////////////////

	listen(sockfd,60);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 	(struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) 
		error("ERROR on accept");
	bzero(buffer,buffer_size);
	
	//n = read(newsockfd,buffer,buffer_size-1);
	//IMPORTANT TO NOTE! when you run functions like saveFile, recv, and sendfile, 
	//They mess with the actual file descriptor by offsetting the value as it readsa
	//leading to fd being empty with done. you may need to make multiple copies of fd
	//also not at this moment, you must alter wav player by removing first four bytes 
	
	//n = recv(newsockfd, buffer, buffer_size-1, MSG_WAITALL);
	//printf("the bytes read from socket is %d \n", n);

	n = read(newsockfd, buffer, 255);
	if (n < 0) error("ERROR reading from socket");
	//SUCCESS IF REACHED HERE ///
	printf("Here is the message: %s \n",buffer);
//	n = write(newsockfd, "jarvis says", 11); 
	char message[buffer_size];
	strcpy(message, speechToText("output.wav"));
	//now we must grab text file information, place here as string 
	//FILE* message = fopen("words.txt", "r");
//	printf("it wrote jarvis says \n");
	n = write(newsockfd, "jarvis says", 11);
	if (n < 0) error("ERROR writing to socket");
	while(n = read(newsockfd,buffer,256) & strcmp(buffer, "ready") != 0 )
	{ 
		n = write(newsockfd, message, 256);
	}	
	n = write(newsockfd, message, 256);
	if (n < 0) error("ERROR writing to socket");
	close(newsockfd);
	close(sockfd);
	return 0; 
}

void saveFile(char* buffer, int fd)
{
	FILE *f = fopen("output3.wav", "wb");
	int fdout = open("output3.wav", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	ssize_t nrd;
	while(nrd = read(fd,buffer,50))
	{
		//printf("its in the while loop \n");
		write(fdout, buffer, nrd);
	}
	fclose(f);
	printf("it gets to the save the file? \n");
}

char* speechToText(char* filename)
{
	printf("does it get to start of speechtoText \n");
	pid_t child, wpid;
	int status =0;
	FILE* cmusphinx;
	int cmuStatus;

//	child = fork();
//	char* phrase;
/*	if(child)
//	{
		
//		printf("\n");
		wait(&status);
	}
	else */
//	{
	//char* args[9] = {"pocketsphinx_continuous", "-infile", "output.wav", "-logfn", "nul", "|", "tee", "./words.txt", 0};
		cmusphinx = popen("pocketsphinx_continuous -infile output.wav -logfn nul | tee ./words.txt", "w");
		cmuStatus = pclose(cmusphinx);
//		exit(0);
	//execv("/usr/bin/pocketsphinx_continuous", args );
		//cmuStatus = pclose(cmusphinx);
//	}
//	while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes
	//get the phrase inside words.txt
	printf("it gets to end of speech to text only once");
	return "test"; 
}

char* fileString()
{
	char* phrase;
	printf("passss while loop");
	FILE* inFile = fopen("words.txt", "r");
	if (inFile = NULL)
	{
		printf(" cannot find file specified");
		return phrase = "";
	}
	else
	{
		printf("gets to else statement");
		long lsize = ftell(inFile);
		phrase = calloc(1, lsize+2); //alocate memory
		
		if(!phrase)
		{
		fclose(inFile);
		printf("memory alloc failure!\n");
		exit(1);
		}

		if(1 != fread(phrase, lsize, 1, inFile))
		{
			fclose(inFile);
			free(phrase);
			printf("buffer failure\n");
			exit(1);
		} //sends buffer
		printf("closes infile before");
		fclose(inFile);
		printf ("phrase: %d\n", phrase);
	}
}
