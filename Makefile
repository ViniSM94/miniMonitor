all: monitor.o
	g++ monitor.o -o monitor -lboost_system

monitor.o: monitor.cpp	
	g++ -c monitor.cpp -std=c++11
