CFLAGS = -Wall -g -std=c++11
HEADERS = BiDijkstraSolver.h \
	  Graph.h \
	  WeightedDirectedGraph.h \
	  WeightedEdge.h \
	  pq/ExtrinsicMinPQ.h

test: test.cpp $(HEADERS)
	g++ $(CFLAGS) -o test test.cpp

clean:
	rm test *.o -f *~
