#!/bin/bash

rsync -avz -e "ssh -p 33 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null/" --progress output.wav masa@192.168.0.114:/home/masa/wavfiles
