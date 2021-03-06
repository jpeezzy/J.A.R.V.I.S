//COMMAND CLASS, TELLS THE AI WHAT TO DO 
#include "commands.h" 
#include "user.h"
#include "Personality.h"
#include <algorithm>
#include <ctype.h>
//#include <simplemenu.h> //gui that lets user send information to backend;
//typedef void(*)(void) function1;
#include <mutex> //std::mutex, std::unique_lock
#include <condition_variable> //std::condition_variable
commands::commands()
{
	wiki = new websearch();
	//heapsize = 21000000;
	heapsize= 8000000;
	load_init_size = 1; 
	//myTime = myClock();
	setMap();
	/*THREAD TO CONSTANTLY CHECK TO LAUNCH ALARM */ 
	clockThread = std::thread(&myClock::waitAlarm, &myTime); //use &myTime instead of myTime. if you do'nt thread will make an extra copy of it :/
}

void commands::talk(std::string text)
{
	festival_say_text(EST_String(text.c_str()));
}

void commands::giveInfo(std::string question)
{	
	ifstream inFile2;
	EST_String newQuestion = EST_String(question.c_str());
	question = Personality::getKeyWords(question);
	std::string directory = "network/infoFiles/" + question + ".txt";
	inFile2.open(directory.c_str());
	std::string realInfo; //what the machine will say
	if(!inFile2)
	{
		//wiki = new websearch();
		//websearch *curl = new websearch(question);
		wiki->searchTopic(question);
		//std::cout << curl -> getString()<< std::endl;
		realInfo = wiki->getString();
		 //need this to be ignored if not there
	}
	else
	{
		std::getline(inFile2,realInfo);
		std::cout << realInfo << std::endl;
	}
	www(question); //searches the question, opening a web browser
	talk(realInfo);
}

void commands::intro()
{
	festival_initialize(load_init_size, heapsize);
	//festival_eval_command("(voice_en1_mbrola)"); //festival must be initialized here or you get error when multithreading
	festival_eval_command("(voice_kal_diphone)");
	ifstream inFile;
	inFile.open("txtFiles/userInfo.txt");
	if(!inFile)
	{
		talk("Hello User. I am JARVIS. What is your name?");
		std::string tempName;
		char* age = new char[3];
		cout << "Type your name: "; cin >> tempName;
		cout << "Type your age: "; cin >> age; 
		cout << "your name is " << tempName << endl;
		user newUser((char*)tempName.c_str(), age);
		newUser.storeInformation((char*)tempName.c_str(), age);
		talk("Hello " + tempName + ". How can I assist you?");
	}
	else
	{ 
		string name;
		std::getline(inFile, name);
		//talk("Welcome back " + name + ". What do you need?");
	}
	idle();
}

void commands::idle() 
{
	std::mutex mtx;
	std::condition_variable cv;
	std::unique_lock<std::mutex> lck(mtx);
	//question = "a";
	while(true)
	{
		//cv.wait(lck, [this]{return !question.compare(qTemp);}); 
		if(question.compare(""))
		{
//			std::cout <<"gets to while loop" << std::endl;
			task(question);
			question = ""; //resets question after finishing
		}
		else 
		{
			usleep(1000000);
		}			
		//cv = std::condition_variable{};
		//mtx = std::mutex{};
		//lck = std::unique_lock{mtx};
		//ifstream inFile2;
//		cout <<"Ask me a Question: ";getline(cin,question);
		//EST_String newQuestion = EST_String(question.c_str());
	//festival_say_text("I do not understand your question:. " + newQuestion + ". Would you like me to google it?");
	//cout << "y/n?"; cin >> ans;
	}
}

void commands::storeQuestion(std::string _question)
{
	question = _question;
	//task(question);
};

void commands::task(std::string question)
{
	if(question.empty())
		return;
	std::vector<std::string> svect;
	std::vector<std::string> saveVector;
	bool phrase = false; 
	for(std::map<std::vector<std::string>, mapTypes>::iterator it=keyWords.begin(); 
			it != keyWords.end(); it++)
	{
		svect = it->first; 
		//std::cout << svect.at(0) <<std::endl;
		for(int i=0; i < it->first.size();i++)
		{
			if(question.find(svect.at(i)) != -1)
			{
				phrase = true;
				saveVector = svect;  
			}
			else if(question.find(svect.at(i)) == -1)
			{
				phrase = false;
				saveVector.clear();
				break;
			}
		}
		if(phrase)//if phrase is still correct at end of loop it is a valid phrase;
		{
			chooseFunct(keyWords[saveVector], question);
			//(*this.*keyWords[saveVector].noFunction)();
			break;
		}
	}
	if(!phrase) //if at the end phrase is false
	{
		talk("I do not understand your question.");
		talk(question);
		talk("Please try again");
	}
}

void commands::chooseFunct(mapTypes mapStruct, std::string question)
{
	if(mapStruct.noFunction!=NULL && mapStruct.strFunct != NULL)
		(*this.*mapStruct.strFunct)(question);
	else if(mapStruct.noFunction != NULL)
		(*this.*mapStruct.noFunction)();
	else if(mapStruct.strFunct != NULL)
		(*this.*mapStruct.strFunct)(question);
}
void commands::setAlarm()
{
	talk("what time sir?");
	int hour;
	int minute;
	std::string AP;
	std::cin >>  hour; 
	std::cin >>  minute;
	std::cin >> AP;
	talk("right away sir. your alarm is at" + std::to_string(hour) + std::to_string(minute));
	myTime.setAlarm(hour, minute, AP);
	//clockThread = std::thread(&myClock::setAlarm, &myTime, hour, minute, AP); //use &myTime instead of myTime. if you do'nt thread will make an extra copy of it :/
}
void commands::endAlarm() 
{
	myTime.endAlarm();
}

void commands::showAlarmTime()
{
	myTime.getAlarmTime();
}
void commands::getTime()
{
	talk("it is " + myTime.getTime());
}


void commands::playMusic(std::string question)
 {
	 unique_lock<mutex> lock(_mutex); //synchronize equivalent
	 //e.g. string format: play some classical music. music is at the end, play is first
//http://id3lib.sourceforge.net/ may use this later to actually get metadata. 
	std::string keyword = question; //foflder to search for music
	try{
	keyword.erase(keyword.find("play"), 4);	
	//std::cout << keyword << std::endl;
	keyword.erase(keyword.find("music"),5); 
	//std::cout << keyword << std::endl;
	keyword.erase(std::remove_if(keyword.begin(),keyword.end(), ::isspace), keyword.end());
	keyword.erase(keyword.find("some"),4);
	//std::cout << keyword << std::endl;
	}catch(std::out_of_range e){std::cout <<"error at try" << std::endl;}// folder to search stuff in; 
	//play some music
	talk("Right away sir");
	if(!myTunes.playMusic(keyword))
	{
		talk("sir, there seems to be an issue with finding the music folders");
	};
	//idle();
	//std::cout <<"does it get to end of plyamusic?" << std::endl;
 }

void commands::playMusic()
{
	talk("right away sir");
	myTunes.playMusic("");
}

void commands::stopMusic()
{
	myTunes.stopMusic();
}
void commands::setMap()
{
	void(*noFunction)(void) = NULL;
	std::vector<std::string> key(10);
	//void(commands::*value)(void);
	//(*this.*keyWords[test].noFunction)();
	//std::vector<std::string> test = {"test", "test"};
	//keyWords[vector<std::string>{"set", "alarm"}].noFunction = &commands::setAlarm;
	abstractMap({"set", "alarm"}, &commands::setAlarm);
	abstractMap({"stop", "alarm"}, &commands::endAlarm);
	abstractMap({"play","music"}, &commands::playMusic);
	abstractMap({"stop","music"}, &commands::stopMusic);
	abstractMap({"meaning","life"}, &commands::meaningOfLife);
	abstractMap({"time"}, &commands::getTime);
	abstractMap({ "alarm", "time"}, &commands::showAlarmTime);
	abstractMap({"hello"}, &commands::greeting);
	abstractMap({"weather"}, &commands::getWeather);
	//this funcitonn will hopefully use the internet 
	abstractMapStr({"go to"}, &commands::launchBrowser); 
	/////
	abstractMapStr({"what"}, &commands::giveInfo);
	abstractMapStr({"who"}, &commands::giveInfo);
	abstractMap({"play","music"}, &commands::playMusic);
	//void(commands::*pointtest)(void) = keyWords[test].noFunction;	
}

void commands::abstractMap(vector<std::string> key, void(commands::*value)(void))
{
	keyWords[key].noFunction = value; 
}

void commands::abstractMapStr(vector<std::string> key, void(commands::*value)(std::string))
{
	keyWords[key].strFunct = value; 
}

void commands::meaningOfLife()
{
	talk("its 42");
	talk("DUMB SHIT");
}

void commands::greeting()
{
	talk("Hello.");
	talk("Jarvis here.");
}

void commands::launchBrowser(std::string Query)
{
	Query.erase(Query.find("go to "), 6);
	www(Query);
}

void commands::getWeather(){
	std::string temp = www.weather();
	talk("the temperature is " + temp + "degrees Fahrenheit");
	//talk(" degrees. Make sure to wear something");
	//method that asys what to wear
}; 
