#include "internet.h"

void internet::browser(std::string website) //launches browser and goes to specific website
{
	char* const args[3] = {(char*)"xdg-open", (char*)website.c_str(), (char*)0}; 
	execv("/usr/bin/xdg-open", args);
	//execv("/usr/bin/xdg-open", (char* const*)website.c_str());
	//std::cout <<(char*)website.c_str() << std::endl;
	exit(EXIT_SUCCESS);
}

internet::internet(): inFile("txtFiles/websites.txt") //OBJECTS ARE DIRECTORY DEPENDENT. E.G.I made an object in jarvis/src, then infile will start looking for the file from THAT directory, not where the c++ file is currently;
{
	std::string  key;
	std::string value; 
	 while(inFile >> key >> value)
	 {
		 sites[key] = value;
	 }
}
std::string internet::websiteURL(std::string website)
{
	if(sites.find(website) != sites.end())
		return sites[website];
	else
	//check textfile and tries to look for a match
		return "https://www.google.com/search?q=" +website; 
}

size_t internet::CurlWrite_CallbackFunc_StdString(void *contents,size_t size,size_t nmemb, std::string *s)
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

std::string internet::getText(std::string url)
{
	std::string text;
    CURL* curl;		    
	CURLcode result; //will give you error code if getting informaiton fails
	curl = curl_easy_init();
	
	//Checks wikipedia for an article to search from
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	std::cout << "URL IS " << url << std::endl;
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);//verify for https://
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);	
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &text);

	result = curl_easy_perform(curl);
		(result!=CURLE_OK) && fprintf(stderr, "curl_easy_perform() failed: %s\n",
				                    curl_easy_strerror(result));
	curl_easy_cleanup(curl); //always cleanup
	//std::cout<<"PRINTING LINES NOW " << std::endl;
	//std::cout << s << std::endl;
	return text;
}


std::string internet::getLocation() //gets current location based on ip address
{
	return getText("http://freegeoip.net/json/"); //keep in mind you only get 15000 of these an hour 
}
std::string internet::weather() 
{
	std::string Location = getLocation(); //find out location based on ip address
	getText("http://api.openweathermap.org/data/2.5/weather?q=Los%20Angeles&appid=13098574849c3ecded8a4fc7d0e2ab4c&units=imperial");
}
