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

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

void uploadFile(char* buffer, char* filename, int outputsocket);

void recordVoice();
void saveFile(char* buffer, int fd);

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}

	pid_t child1;
	int status =0;		
	child1 = fork();
	if(child1)
	{
		printf("\n");
		wait(&status);
	}
	else
		recordVoice();

	portno = atoi(argv[2]); //THIS IS WHERE PORT IS AT. 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	printf("does it get past recordVoice?\n");
	//we are going to use stat to grab the size 
	//of the output.wav based on its file desciptor and place it in a buffer 
	//int input_file = open("output.wav", O_RDONLY); //OPESN FILE
	//struct stat st;
	//stat((const char * restrict)input_file, &st);
	char buffer[256];
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

	//TRYING TO READ DATA INTO BUFFER
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
		uploadFile(buffer, "output.wav", sockfd);
		exit(0);
	}
	while((wpid = wait(&status2)) > 0);

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
	printf("%s \n",buffer);
//	printf("%s \n",buffer);
	if (n < 0) 
		error("ERROR reading from socket");

	//int input_file = open("sample.wav", O_RDONLY); //OPESN FILE
	//	printf("this is what the buffer says: %d \n", buffer);
	close(sockfd);
	return 0;
}

void uploadFile(char* buffer, char* filename, int output_socket)
{
//x230	
//char* server = "masa@192.168.0.114:/home/masa/wavfiles";
//t60
	char* server = "masa@192.168.29.119:/home/masa/jarvis/server/server";
//	char sshLong[200] = "ssh -p "; //x230
	char sshLong[200] = "ssh "; //x230
//	char* port = "33"; x230
	char* port = ""; //t60
	printf("ssh: %s", sshLong);
	strcat(sshLong, port);
	printf("ssh: %s", sshLong);
	char* sshcont = " -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null/";
	strcat(sshLong, sshcont);
	printf("ssh: %s", sshLong);
	char* args[8] = {"rsync", "-avz", "-e", sshLong, "--progress", filename, server, 0};
	execv("/usr/bin/rsync", args);
/*	struct stat sb; 
	int fd = open("output.wav", O_RDONLY);
	int fd2 = open("output.wav", O_RDONLY);
	fstat(fd, &sb);
	// first send the file size - NB this is not correct as it
	// assumes sizeof( sb.st_size ) is the same on the other
	// end *and* has the same endianness
	// first send the file size - NB this is not correct as it
	write( output_socket, &sb.st_size, sizeof( sb.st_size ) );
	ssize_t bytesSent = sendfile( output_socket, fd, NULL, sb.st_size );
	printf("bytes sent is %zu \n", bytesSent);
	saveFile(buffer, fd2); */
}

void recordVoice()
{
	printf("RECORDING FILE NOW");
	char* const args[11] = {"rec", "-r", "16000", "-c", "1", "-d", "output.wav", "trim", "0", "5", 0};
	execv("/usr/bin/sox", args);
}

void saveFile(char* buffer, int fd)
{
	FILE *f = fopen("output3.wav", "wb");
	int fdout = open("output3.wav", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	ssize_t nrd;
	while(nrd = read(fd,buffer,50))
	{
		printf("");
		write(fdout, buffer, nrd);
	}
	fclose(f);
	printf("it gets to the save the file? \n");
}
