HEADER = /usr/include/festival/
HEADER2 = /usr/include/speech_tools/
HEADER3 = ~/jarvis/network/
HEADER4 = ~/jarvis/src/
LINK1 = /usr/lib/festival/
LINK2 = /usr/lib/speech_tools/
LINK3 = ~/jarvis/lib/
LINK4 = ~/jarvis/src/
test: $(HEADER) main.cpp
	g++ -std=c++11 -g -I $(HEADER) -I $(HEADER2) -I $(HEADER3) -I $(HEADER4) -o test network/websearch.cpp main.cpp src/user.cpp personality/Personality.cpp -L $(LINK1) -lFestival -L $(LINK2) -ltermcap -lestools -lestbase -leststring -lncurses -lcurl
	


#alright in order to link a library, you have to first -List the path of the directory(-L) then IMMEDIETLY link the library using -l. 
