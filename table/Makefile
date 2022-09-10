BUILD=./build
LIB=../src
INCLUDE=./include

a:
	gcc -O3 -I$(INCLUDE) -I../include \
	-o $(BUILD)/a.out main.c \
	$(LIB)/*.c 

debug:
	gcc -g -O1 -I$(INCLUDE) -I../include \
	-o $(BUILD)/debug main.c \
	$(LIB)/*.c 

test:
	gcc -o $(BUILD)/$@ test.c $(LIB)/word-freqs.c

