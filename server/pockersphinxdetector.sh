#!/bin/bash
rec -r 16000 -c 1 -d ~/output.wav trim 0 5
# this  script takes a wav file, parses it, and sends it to output txt file, where it then can be grabbed 
pocketsphinx_continuous -infile output.wav -logfn nul | tee ./words.txt
