Ok, I got it to speak hello world. This is amazing. here is what you need.
1.http://www.cstr.ed.ac.uk/downloads/festival/2.4/
download everything on that page.(I did not use speech_tools2.4 with wrapper).  

2.Use my makefile. I went through alot of crap to find how to use one. You need to use -laudio.
#there's an issue with makefiling (I currently have an i686 architecture). You'll need to make all the files you downloaded on your own (will try to fix at a later point)
3.http://www.cstr.ed.ac.uk/projects/festival/manual/festival_28.html
use this link to go to C/C++ api and check the samplecode/functions

4. put a .festivalrc file in home directory (will not work without it);

PROCEDURE:

1. after downloading everything, tar xvf all the files. Then go to the festival folder and make(this will take a while). Simultaneously you can also make the speech_tools. (you will need this later)

2. after wards, make the rest of the files. This is crucial. After doing this, you should have a festival and speech folder filled with the libraries/speech api that I have. 

3. use my make file and cpp file to make sound come out. 

4. Afterwards, create a .festivalrc file and follow the steps below(the dsp/dev error)
https://wiki.archlinux.org/index.php/Festival#Can.27t_open_.2Fdev.2Fdsp

5. You will now need a few libraries you'll have to install on your own. Here is what you need: 
sudo apt-get install curl libcurl4-gnutls-dev   
(ubuntu) (You'll have to figure it out with your own unix distribution)

