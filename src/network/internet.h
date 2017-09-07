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
#include <curl/curl.h> ///for CURL
#include "json.hpp" //json parser
class internet 
{
	private:
		pid_t child1;
		std::ifstream inFile;
		std::map<std::string, std::string> sites;
	public:
		internet();
		static size_t CurlWrite_CallbackFunc_StdString(void *contents,size_t size,size_t nmemb, std::string *s);
		void browser(std::string website); //opens browser;
		std::string websiteURL(std::string website); //gets phrase and finds website;
		void websearch();
		std::string getText(std::string url); //should return all words from a website;
		std::string getLocation(); //finds location based on ip address 
		std::string weather(); //gets the weather 
		std::string whatToWear(); //what to wear based on weather
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
				browser(website);
			}
		}; //function that launches based on website;

};





#endif
