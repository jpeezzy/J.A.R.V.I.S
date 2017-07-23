#include <curl/curl.h>
#include <iostream>
#include <algorithm> //std::copy_if
#include <vector>
#include <fstream>
#include "websearch.h"
#include <map>
//we'll need to implement a callback function here (unavoidable) (sending a function pointer as an arg. for another function. 
#include <string> 
size_t CurlWrite_CallbackFunc_StdString(void *contents,size_t size,size_t nmemb, std::string *s)
{
	//callback function that writes the contents of a webpage to a string.
	size_t newLength = size*nmemb;
	size_t oldLength = s->size();
	try
	{
		s->resize(oldLength + newLength);
		//std::cout << s->size() << std::endl;
	}
	catch(std::bad_alloc &e)
	{
		std::cout<<"Is there bad memory?"<<std::endl;
		//handle mem problem
		return 0;
	}
	char* first = (char*)contents;
	char* last = (char*)contents + newLength;
	std::copy(first,last,s->begin()+oldLength);
	return size*nmemb;
}

void websearch::storeInformation(std::string name,std::string information)
{
	//pushes stored information to a txt file so the main program can read it;
	std::string textName = "network/infoFiles/" + name + ".txt";
	///std::cout << "stored information is called" << name << std::endl;
	char* textNameReal = (char*)textName.c_str();
	std::ofstream myfile(textNameReal);
	myfile << information;
	//std::cout << "does it store infomration???" << std::endl;
	myfile.close();
}

websearch::websearch(std::string topicName) {
	topic = topicName;
	s;
    CURL* curl;		    
	CURLcode result; //will give you error code if getting informaiton fails
	curl = curl_easy_init();
	std::string url = "https://en.wikipedia.org/wiki/" + topicName + "?%20action=render"; 
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	std::cout << "URL IS " << url << std::endl;
	//curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/search?q=curl&oq=curl+&aqs=chrome..69i57j69i60l5.1389j0j7&client=ubuntu&sourceid=chrome&ie=UTF-8");
	//curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //verify for https://
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);//verify for https://
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);	
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

	result = curl_easy_perform(curl);
		(result!=CURLE_OK) && fprintf(stderr, "curl_easy_perform() failed: %s\n",
				                    curl_easy_strerror(result));
	curl_easy_cleanup(curl); //always cleanup
	//std::cout<<"PRINTING LINES NOW " << std::endl;
	//std::cout << s << std::endl;
	try{
		s =cleanupInformation(s);
	//now we must cleanup the string
	} catch(const std::exception& e){
		s = "I can't seem to find the information you are looking for. PLEASE try again sir.";
		//pro tip: to pause the machine make your word all caps. 
		//std::cout <<"the page is not found. please try again" << std::endl;
		//return;
	}; //need this to be ignored if not there
	//std::cout << s << std::endl; //maybe send s to an html file?
	storeInformation(topic,s);
	//std::cout <<"PROGRAM DONE" <<std::endl;
	//now separate the strings maybe using recursion ??? for loop seems better (remove tags)
	//std::cout << "Position is at "<< position << std::endl;
}

std::string websearch::getString()
{
	return s; 
}
std::string websearch::cleanupInformation(std::string information)
{
	std::map<char, char> couples;
	couples['<'] = '>';
	couples['('] = ')';
	couples['['] = ']';

	//now we need to trim down the search (to the intro paragraph of the wikipedia article);
	size_t position0 = s.find("This article",0); //gets rid of text on top of page
	size_t position1 = s.find_first_of('\n', position0);
	try{
	s.erase(position0,position1);
	} catch(const std::exception& e){}; //need this to be ignored if not theri
	//std::cout << s <<std::endl;
	size_t bioLength[] = {s.find(" is a",0), s.find(" are a",0), s.find(" was a",0), s.find(" were a", 0)};
	size_t position = bioLength[0];
	for(int x =1; x <sizeof(bioLength)/sizeof(*bioLength); x++)
	{
		position = (position < bioLength[x])? position: bioLength[x];
		//std::cout << "Position for is a is " << position <<  std::endl;
	}
		//we're probably goona have to make a comparison with which line is first is, who, were etc
	size_t position2 = s.find('\n', position);
	std::string newS = s.substr(position, position2-position);
	//std::cout << newS << std::endl;
	//std::cout<<"does it ever delete this article?"<<std::endl;
	int i = 0;
	int size = newS.size();
	while( i < size)
	{
	//std::cout<<"does it ever delete this article?"<<std::endl;
		if(newS.at(i) == ('<'))
		{
			//std::cout <<"gets to here?" <<std::endl;
			//s.erase(i,s.find('>'));
			while(newS.at(i) != '>')
			{
			newS.erase(i, 1); size--;
			}
			newS.erase(i,1); size--;
		}
		else if(newS.at(i) == '(')
		{
			while(newS.at(i) != ')')
			{
				//std::cout <<"gets to here" <<std::endl;
				newS.erase(i,1); size--;
			}
			newS.erase(i,1); size--; 
		}
		else if(newS.at(i) == '[')
		{
			while(newS.at(i) != ']')
			{
			//std::cout << "it gets to here. position of next one is " <<newS.find(']') <<std::endl; 
			newS.erase(i,1); size--;	
			}
			newS.erase(i,1); size--;
		}
		else
			i++;
	}

	//std::cout << newS << std::endl;
	i = 0;
	while( i< size)
	{
		if(newS.at(i) == '[')
		{
			while(newS.at(i) != ']')
			{
			std::cout << "it gets to here. position of next one is " <<newS.find(']') <<std::endl; 
			newS.erase(i,1); size--;	
			}
			newS.erase(i,1); size--;
		}
		else
			i++;
	}
	//std::cout << newS << std::endl;
	newS = topic + newS;
	return newS;
}
//https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
