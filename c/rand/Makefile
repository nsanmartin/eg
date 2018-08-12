OBJECTS = ./build/random-bytes.o

random-bytes.o:
	gcc -c -O3 -o ./build/random-bytes.o random-bytes.c


test-randbytes: random-bytes.o
	gcc -O3  ./build/random-bytes.o -o ./build/test-randbytes \
	./tests/test-randbytes.c

librandbytes: random-bytes.o
	ar rcs $(HOME)/lib/$@.a build/random-bytes.o && \
	cp librandbytes.h $(HOME)/include/

clean:
	rm ./build/*
