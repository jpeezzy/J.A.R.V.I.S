#include "internet.h"

internet::internet(): inFile("txtFiles/websites.txt")
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
	//check textfile and tries to look for a match
	return sites[website]; 
}

