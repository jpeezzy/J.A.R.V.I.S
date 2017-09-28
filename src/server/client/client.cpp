#include "client.h"
#include "commands.h"

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
	char* server = (char*)"masa@192.168.29.119:/home/masa/jarvis/server/server";
//	char sshLong[200] = "ssh -p "; //x230
	char sshLong[200] = "ssh "; //x230
//	char* port = "33"; x230
	char* port = (char*)""; //t60
	printf("ssh: %s", sshLong);
	strcat(sshLong, port);
	printf("ssh: %s", sshLong);
	char* sshcont = (char*)" -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null/";
	strcat(sshLong, sshcont);
	printf("ssh: %s", sshLong);
	char* args[8] = {(char*)"rsync", (char*)"-avz", (char*)"-e", (char*)sshLong, (char*)"--progress", (char*)filename, (char*)server, 0};
	execv("/usr/bin/rsync", args);
}


