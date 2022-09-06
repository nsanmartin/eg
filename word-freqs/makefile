BUILD=./build
LIB=./src
INCLUDE=./include

bench:
	gcc -O3 -I$(INCLUDE) -o $(BUILD)/ver-read ver-read.c $(LIB)/*.c
	gcc -O3 -I$(INCLUDE) -o $(BUILD)/ver-fgets ver-fgets.c
	gcc -O3 -I$(INCLUDE) -o $(BUILD)/ver-getline ver-getline.c
	g++ -O3 -I$(INCLUDE) -o $(BUILD)/ver-cin ver-cin.cpp
	ghc -no-keep-o-files -no-keep-hi-files -O2 ver-words.hs -o $(BUILD)/ver-words
	cp ver-split.py $(BUILD)/ver-split

debug:
	gcc -g -I$(INCLUDE) -o $(BUILD)/debug-read ver-read.c $(LIB)/*.c

test:
	gcc -o $(BUILD)/$@ test.c $(LIB)/word-freqs.c

