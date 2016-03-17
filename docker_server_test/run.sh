#!/bin/bash
sudo docker run -p 9999:80 -ti --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix server_test
