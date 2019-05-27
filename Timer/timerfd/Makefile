CXX = g++
CXXFLAGS = -Wall -g -pthread -std=c++11
INCLUDE = -I.

obj := timerfd.o
target := main

main:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c timerfd.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(obj) main.cxx -o $@

clean:
	rm -rf *.o $(target)
	
