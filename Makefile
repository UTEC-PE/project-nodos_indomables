CXX = g++
SRCS = main.cpp

HDIR = include
INC = -I $(HDIR)
CXXFLAGS = -std=c++14 $(INC)

all: run

main: $(SRCS) $(HDIR)/*.h
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

run: main
	@echo " Running..."
	clear
	clear
	./main
