all: main

main: main.cpp read.h graph.h node.h edge.h
	g++ -std=c++11 main.cpp -o main
