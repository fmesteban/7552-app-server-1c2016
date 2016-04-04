#!/bin/sh

echo 'Running cpplint'
python cpplint.py `find -regextype posix-egrep -regex './AppServer/src/web_server/.*\.(h|hpp|c|cpp)'`

if [ $? -ne 0 ]
then
    echo "Can't commit! You have cpplint offences"
    exit 1
fi

echo "All checks passed."
exit 0
