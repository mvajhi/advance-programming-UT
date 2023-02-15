#!/bin/bash
g++ main.cpp -o main

if [$? -eq 0];
then
	./main < input.txt
fi
