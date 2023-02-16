#!/bin/bash
g++ -std=c++11 main.cpp -o main

if [ $? -eq 0 ];
then
	./main < input.txt
else
	echo "faild"
fi
