//COMMAND CLASS, TELLS THE AI WHAT TO DO 

#include "commands.h" 
#include <iostream>
#include <festival.h> 
#include <EST_String.h>

commands::commands()
{
	heapsize = 21000000;
	load_init_size = 1; 
	festival_initialize(load_init_size, heapsize);
	festival_eval_command("(voice_ked_diphone)");
}

void commands::talk(EST_String text)
{
	festival_say_text(text);
}
