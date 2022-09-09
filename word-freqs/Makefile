BUILD=./build
LIB=../src
INCLUDE=./include 
INCLUDE_LAMBDA=../include
bench:
	gcc -O3 -I$(INCLUDE) -I$(INCLUDE_LAMBDA) -o $(BUILD)/ver-read ver-read.c $(LIB)/*.c ./src/*.c
	gcc -O3 -I$(INCLUDE) -I$(INCLUDE_LAMBDA) -o $(BUILD)/ver-fgets ver-fgets.c $(LIB)/*.c ./src/*.c

	gcc -O3 -I$(INCLUDE) -I$(INCLUDE_LAMBDA) -o $(BUILD)/ver-getline ver-getline.c
	g++ -O3 -I$(INCLUDE) -I$(INCLUDE_LAMBDA) -o $(BUILD)/ver-cin ver-cin.cpp
	ghc -no-keep-o-files -no-keep-hi-files -O2 ver-words.hs -o $(BUILD)/ver-words
	cp ver-split.py $(BUILD)/ver-split

debug:
	gcc -O1 -g -I$(INCLUDE) -I$(INCLUDE_LAMBDA) -o $(BUILD)/debug-read ver-fgets.c $(LIB)/*.c

test:
	gcc -o $(BUILD)/$@ test.c $(LIB)/word-freqs.c

