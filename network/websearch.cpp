#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <algorithm> //std::copy_if
#include <vector>
#include <fstream>
//we'll need to implement a callback function here (unavoidable) (sending a function pointer as an arg. for another function. 
#include <string> 
size_t CurlWrite_CallbackFunc_StdString(void *contents,size_t size,size_t nmemb, std::string *s)
{
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

void storeInformation(std::string name,std::string information)
{
	std::string textName = "infoFiles/" + name + ".txt";
	char* textNameReal = (char*)textName.c_str();
	std::ofstream myfile(textNameReal);
	myfile << information;
	myfile.close();

}
//https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string
int main(void) {
	std::string s;
    CURL* curl;		    
	CURLcode result; //will give you error code if getting informaiton fails
	curl = curl_easy_init();

	curl_easy_setopt(curl, CURLOPT_URL, "https://en.wikipedia.org/wiki/CURL?%20action=render");
	//curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/search?q=curl&oq=curl+&aqs=chrome..69i57j69i60l5.1389j0j7&client=ubuntu&sourceid=chrome&ie=UTF-8");
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //verify for https://
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);//verify for https://
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString);	
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
	
	result = curl_easy_perform(curl);
	if(result != CURLE_OK)
	{
		fprintf(stderr, "curl_easy_perform() failed: %s\n",
				                    curl_easy_strerror(result));
	}
	curl_easy_cleanup(curl); //always cleanup
	std::cout<<"PRINTING LINES NOW " << std::endl;
	//now we must cleanup the string
	int size = s.size();
	int i =0;
	while( i < size)
	{
		if(s.at(i) == ('<'))
		{
			//std::cout <<"gets to here?" <<std::endl;
			while(s.at(i) != '>')
			{
			s.erase(i, 1); size--;
			}
			s.erase(i,1); size--;
		}
		else if(s.at(i) == '(')
		{
			while(s.at(i) != ')')
			{
				//std::cout <<"gets to here" <<std::endl;
				s.erase(i,1); size--;
			}
			s.erase(i,1); size--; 
		}
		else
			i++;
	}
	//now we need to trim down the search (to the intro paragraph of the wikipedia article);	
	size_t position = s.find("cURL  is" , 0);
	size_t position2 = s.find_first_of('\n', position);
	s.erase(position2, std::string::npos);
	s.erase(0,position);
	int x = s.size();
	std::cout <<"position 2 is at " << position2 <<std::endl;
	std::cout << s << std::endl; //maybe send s to an html file?
	storeInformation("cURL",s);
	std::cout <<"PROGRAM DONE" <<std::endl;
	//now separate the strings maybe using recursion ??? for loop seems better (remove tags)
	//std::cout << "Position is at "<< position << std::endl;
	return 0;
}
