BUILD=./build
LIB=./src
INCLUDE=./include
WORD_FREQS=../word-freqs
a:
	gcc -O3 -I$(INCLUDE) -I$(WORD_FREQS)/include \
	-o $(BUILD)/a.out main.c \
	$(LIB)/*.c $(WORD_FREQS)/src/do-words.c

debug:
	gcc -g -I$(INCLUDE) -o $(BUILD)/debug-read ver-read.c $(LIB)/*.c

test:
	gcc -o $(BUILD)/$@ test.c $(LIB)/word-freqs.c

