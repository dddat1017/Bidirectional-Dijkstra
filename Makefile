CFLAGS = -Wall -g -std=c++11

test: test.cpp WeightedDirectedGraph.h BiDijkstraSolver.h
	g++ $(CFLAGS) -o test test.cpp

clean:
	rm test *.o -f *~
