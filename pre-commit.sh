#!/bin/sh

echo 'Running cpplint'
cpplint --exclude=AppServer/src/third_party/* `find -regextype posix-egrep -regex './AppServer/src/.*\.(h|hpp|c|cpp)'`

if [ $? -ne 0 ]
then
    echo "Can't commit! You have cpplint offences"
    exit 1
fi

echo "All checks passed."
exit 0