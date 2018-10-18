all: run

main: main.cpp *.h
	g++ -std=c++11 main.cpp -o main

run: main
	./main
