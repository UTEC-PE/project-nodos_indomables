all: run

main: main.cpp *.h
	g++ -std=c++14 main.cpp -o main

run: main
	./main
