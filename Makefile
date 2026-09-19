CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

all: josephus

josephus: josephus.cc josephus.h
	$(CXX) $(CXXFLAGS) josephus.cc -o josephus

clean:
	rm -f josephus