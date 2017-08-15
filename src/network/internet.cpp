#include "internet.h"

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

