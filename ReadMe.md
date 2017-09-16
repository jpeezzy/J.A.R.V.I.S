Ok, I got it to speak hello world. This is amazing. here is what you need.

1.Use my makefile. I went through alot of crap to find how to use one. You need to use -laudio.
#there's an issue with makefiling (I currently have an i686 architecture). You'll need to make all the files you downloaded on your own (will try to fix at a later point)

2.http://www.cstr.ed.ac.uk/projects/festival/manual/festival_28.html
use this link to go to C/C++ api and check the samplecode/functions

3. put a .festivalrc file in home directory (will not work without it);

PROCEDURE:

1. You will now need a few libraries you'll have to install on your own. Here is what you need: 
sudo apt-get install curl libcurl4-gnutls-dev festival-dev libestools-dev vlc festvox-en1 festlex-poslex

for Arch linux (**Master Race**)
$ pacman -S festival alsa-utils xdg-utils sox rsync 
$ yaourt -S termcap


(ubuntu) (You'll have to figure it out with your own unix distribution)

2. after wards, make the rest of the files. This is crucial. After doing this, you should have a festival and speech folder filled with the libraries/speech api that I have. 

THIS ONLY WORKS FOR 64 BIT CURRENTLY (WILL TRY TO WORKON 32 BIT MAYBE?)


3. use my make file and cpp file to make sound come out. 

4. Afterwards, create a .festivalrc file and follow the steps below(the dsp/dev error)
https://wiki.archlinux.org/index.php/Festival#Can.27t_open_.2Fdev.2Fdsp

6. get cava (equalizer that opens when you play music. will need
sudo apt-get update
sudo apt-get install m4 )
	https://github.com/karlstav/cava (if needed I can attach my config)
the best command line to use is urxvt for cava performance. you can get it in ubuntu using sudo apt install rxvt-unicode

7. for talking recognition (use pocketsphinx) 
cmusphinx.github.io/wiki/tutorialpocketsphinx/
follow the tutorial and youll be golden. 
