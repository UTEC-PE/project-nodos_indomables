all: main

main: main.cpp read.h
	g++ -std=c++11 main.cpp -o main
