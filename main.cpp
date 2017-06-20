#include <iostream>
#include "festival.h"
#include <EST_String.h>
using namespace std;

int main()
{
	EST_Wave wave;
	int heapsize = 210000;
	int load_init_size = 1;
	festival_initialize(load_init_size, heapsize);
	festival_eval_command("(voice_kal_diphone)");
	festival_say_text("Hello world?");
	cout<<"Hello world. This is a test" <<endl;
	return 123;
}
