//licencing here later 
//
//this header file should hold all the methods that requires launching a web browser; 
#ifndef INTERNET_H
#define INTERNET_H
#include <iostream>
#include <fstream>
#include <stdlib.h> 
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include <map>
class internet
{
	private:
		pid_t child1;
		std::ifstream inFile;
		std::map<std::string, std::string> sites; 
	public:
		internet();
		std::string websiteURL(std::string website); //gets phrase and finds website;

	//	void launchReddit(); //launches reddit
	//	void launchYoutube(); //launches youtube on chrome
	//	maybe use a functor to launch a web page
	//
		void operator () (std::string website)
		{
			website = websiteURL(website); 
			child1 = fork();
			if(child1)
			{
			}
			else
			{
				char* const args[3] = {(char*)"xdg-open", (char*)website.c_str(), (char*)0}; 
				execv("/usr/bin/xdg-open", args);
				//execv("/usr/bin/xdg-open", (char* const*)website.c_str());
				//std::cout <<(char*)website.c_str() << std::endl;
				exit(EXIT_SUCCESS);
			}
		}; //function that launches based on website;

};





#endif
