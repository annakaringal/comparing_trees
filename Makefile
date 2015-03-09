CC = g++
VERS = -std=c++11

all: queryTrees testTrees

queryTrees: queryTrees.cpp SequenceMap.cpp
	$(CC) $(VERS) queryTrees.cpp SequenceMap.cpp -o queryTrees


testTrees: testTrees.cpp SequenceMap.cpp
	$(CC) $(VERS) testTrees.cpp SequenceMap.cpp -o testTrees

clean: 
	rm *o queryTrees testTrees