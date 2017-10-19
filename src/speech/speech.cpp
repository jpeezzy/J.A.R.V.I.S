//******PPART OF PROGRAM THAT MAKES THE COMPUTER TALK
#include "speech.h"

//#ifdef __linux
speech::speech()
{
	heapsize =21000000;
	load_init_size = 1;
	festival_initialize(load_init_size, heapsize);
	//festival_eval_command("(voice_kal_diphone)");
	festival_eval_command("(voice_en1_mbrola)"); //festival must be initialized here or you get error when multithreading
	//speak("it's kind of working");
}

void speech::speak(std::string text)
{
	festival_say_text(EST_String(text.c_str()));
}

//#endif
