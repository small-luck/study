CXX = c++
CXXFLAGS = -std=c++11 -g -W -Wall -lpthread
INCLUDE = -I.

OBJS := event.o net.o rbtree.o timer.o utils.o 
TARGET := main

main:
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c event.cxx 
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c net.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c rbtree.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c timer.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c utils.cxx
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJS) main.cxx -o $@

clean:
	rm -rf *.o $(TARGET)