#ifndef MUSIC_H 
#define MUSIC_H
#include <iostream>
#include <vector>
//https://github.com/karlstav/cava
//use vlc and cava to launch music 
//vlc -ZL --qt-start-minimized Music/MapleStory\ 2\ BGM/
class music
{
	private:
		std::vector<std::string> genre; // http://id3.org/id3v2.3.0 list of genre and number
		pid_t child1;
		pid_t child2; 
	public:
		bool playMusic(std::string fileName); //plays music  
		void stopMusic();	
};
#endif

