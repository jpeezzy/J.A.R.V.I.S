#include <iostream> 
#include "Personality.h"

Personality::Personality(){

};

std::string Personality::getPhrase(){

}

std::string Personality::getKeyWords(std::string phrase){
	//trims the phrase to get keywords
	std::vector<std::string> cutWords(10);
	cutWords[0] = "the ";
	cutWords[1] = "is ";
	cutWords[2] = "what ";
	cutWords[3] = "are ";
	cutWords[4] = "who ";
	cutWords[5] = "were ";
	cutWords[6] = "when ";
	cutWords[7] = "where ";
	cutWords[8] = "why ";
	for(int i =0; i < cutWords.size(); i++)
	{
		try{
	   		if(phrase.find(cutWords[i]) < phrase.length()) 
				(phrase.erase(phrase.find(cutWords[i]),cutWords[i].size()));
		} catch(const std::out_of_range e ){};
	}
	return phrase; 
} 


