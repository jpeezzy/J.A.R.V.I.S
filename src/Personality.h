#ifndef PERSONAILTY_H
#define PERSONALITY_H
#include <fstream> 
#include <iostream>
#include <vector> 
class Personality
{
	private:
		std::string getPhrase(); //gets a personality phrase
		//std::vector<std::string> cutWords(10); //ordered by prominance
	public:
		Personality();
		static std::string getKeyWords(std::string phrase); //get keywords from question
};
#endif
