#!/bin/bash

rsync -avz -e "ssh -p 1337 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null/" --progress words.txt ieee@10.0.0.69:/home/ieee/
