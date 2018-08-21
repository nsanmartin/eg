CXX=g++ 
CXXFLAGS=-g -std=c++11 -Wall

non-const-str-arg:
	$(CXX) $(CXXFLAGS) tests/$@.cpp -o build/$@


non-const-str-arg-measure:
	$(CXX) $(CXXFLAGS) tests/$@.cpp -o build/$@


return-variants-measure:
	$(CXX) $(CXXFLAGS) tests/$@.cpp -o build/$@


sigsegv-recursion:
	$(CXX) $(CXXFLAGS) tests/$@.cpp -o build/$@


clean:
	rm build/*
