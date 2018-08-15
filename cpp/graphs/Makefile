CXXFLAGS=-g -std=c++11

all: tprimkruskal tdijkstra tprint tdantzig


tprimkruskal:
	g++ $(CXXFLAGS) tests/$@.cpp -o build/$@


tdijkstra:
	g++ $(CXXFLAGS) tests/$@.cpp -o build/$@


tprint:
	g++ $(CXXFLAGS) tests/$@.cpp -o build/$@


tdantzig:
	g++ $(CXXFLAGS) tests/$@.cpp -o build/$@

clean:
	rm build/*
