#!/usr/bin/env bash
sudo docker stop app-server
result=`sudo docker ps -a | grep app-server`
if [ ! -z "$result" ]
then
    echo "Server already running."
    sudo docker rm app-server
fi

sudo docker run -i -t -p 8000:8000 --name app-server -v "$PWD":/app-server app-server /app-server/make-and-run-server.sh