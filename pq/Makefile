CFLAGS = -Wall -g -std=c++11

test: test.cpp ExtrinsicMinPQ.h ExtrinsicMinPQ.cpp
	g++ $(CFLAGS) -o $@ $<

clean:
	rm test *.o -f *~
