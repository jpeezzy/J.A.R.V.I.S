//HELLO, this is a BASIC AI that will follow commands based on voice(soon)
//
#include <iostream>
#include "festival.h"
#include <EST_String.h>
using namespace std;

int main()
{
	ofstream myfile;
	EST_Wave wave;
	int heapsize = 21000000;
	int load_init_size = 1;
	festival_initialize(load_init_size, heapsize);
	festival_eval_command("(voice_kal_diphone)");
	festival_say_text("Hello User. I am JARVIS. What is your name?");
	char* tempname = new char[20];
	cout << "Type your name "; cin >> tempname;
	cout << "your name is " << tempname << endl;
	EST_String name = EST_String(tempname);
	festival_say_text("Hello " + name + ". How can I assist you?");
	cout<<"Hello world. This is a test" <<endl;
	//make it so when you ask a question and they don't answer, ask them if they would like to google it.
	//if yes, google and use the first question for an answer.
	//also, look for keywords when they ask something and store them with the answer in a text file somehow.
	//e.g. ([weather,day] - current temperature and date); 
	return 123;
}
