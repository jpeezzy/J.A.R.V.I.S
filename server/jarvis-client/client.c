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

void error(const char *msg)
{
	perror(msg);
	exit(0);
}

void upload_file(char* buffer, char* filename, int outputsocket);

int main(int argc, char *argv[])
{
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;

	char buffer[256];

	if (argc < 3) {
		fprintf(stderr,"usage %s hostname port\n", argv[0]);
		exit(0);
	}

	portno = atoi(argv[2]); //THIS IS WHERE PORT IS AT. 
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, 
			(char *)&serv_addr.sin_addr.s_addr,
			server->h_length);
	serv_addr.sin_port = htons(portno);
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR connecting");

	//TRYING TO READ DATA INTO BUFFER

	/* printf("Please enter the message: ");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0) 
		error("ERROR writing to socket");
	bzero(buffer,256);
	n = read(sockfd,buffer,255);
	if (n < 0) 
		error("ERROR reading from socket");
	printf("%s\n",buffer);
*/
	//int input_file = open("sample.wav", O_RDONLY); //OPESN FILE
	upload_file(buffer, "output.wav", sockfd);
	close(sockfd);
	return 0;
}

void upload_file(char* buffer, char* filename, int output_socket)
{
	int input_file; 
	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	input_file = open(filename, O_RDONLY); //opens the file;
	dup2(input_file, 5);
	//https://stackoverflow.com/questions/2014033/send-and-receive-a-file-in-socket-programming-in-linux-with-c-c-gcc-g
	int bytes_read = read(input_file, buffer, sizeof(buffer));
	if(bytes_read == 0)
		//break;

		if (bytes_read < 0)
		{
			printf("welp, you fucked up. your bytes_read is less than 0 ");
		}

	// You need a loop for the write, because not all of the data may be written
	//     // in one call; write will return how many bytes were written. p keeps
	//         // track of where in the buffer we are, while we decrement bytes_read
	//             // to keep track of how many bytes are left to write.

	void *p = buffer;
	while (bytes_read > 0) {
		int bytes_written = write(output_socket, p, bytes_read);
		if (bytes_written <= 0) {
			// handle errors
		}
		bytes_read -= bytes_written;
		p += bytes_written;
	}

	sendfile(output_socket, input_file, NULL, sizeof(buffer));
	
	printf("does it get to end of uploadfile?");
	return;
	//now implement senfile?
}


