CFLAGS = -Wall -g -std=c++11
HEADERS = Graph.h \
	  WeightedDirectedGraph.h \
	  WeightedEdge.h \
	  ../solver/BiDijkstraSolver.h \
	  ../pq/ExtrinsicMinPQ.h

test: test_weighteddirectedgraph.cpp $(HEADERS)
	g++ $(CFLAGS) -o test_weighteddirectedgraph test_weighteddirectedgraph.cpp

clean:
	rm test_weighteddirectedgraph *.o -f *~
