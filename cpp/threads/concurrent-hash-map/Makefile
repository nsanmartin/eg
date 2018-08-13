CXX = g++
CXXFLAGS = -g -std=c++0x
LDLIBS = -lpthread


all: test0 test1
test0: 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) \
	-o build/$@ $@.cpp $(LDLIBS)

test1:
	$(CXX) $(CXXFLAGS) $(LDFLAGS) \
	-o build/$@ $@.cpp $(LDLIBS)

clean:
	rm build/*
