HEADER = ~/jarvis/festival/src/include/
HEADER2 = ~/jarvis/speech_tools/include/
HEADER3 = ~/jarvis/network/
LINK1 = ~/jarvis/festival/src/lib/
LINK2 = ~/jarvis/speech_tools/lib/
LINK3 = ~/jarvis/lib/
test: $(HEADER) main.cpp
	g++ -std=c++11 -I $(HEADER) -I $(HEADER2) -I $(HEADER3) -o test network/websearch.cpp main.cpp user.cpp -L $(LINK1) -lFestival -L $(LINK2) -ltermcap -lestools -lestbase -leststring -lncurses -lcurl

#alright in order to link a library, you have to first -List the path of the directory(-L) then IMMEDIETLY link the library using -l. 
