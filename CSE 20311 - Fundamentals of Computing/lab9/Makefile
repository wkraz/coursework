# Makefile for lab 9
#   "make" or "make all : creates all three executables
#   "make symbol" : creates the symbol executable
#   (similarly for "make bounce" and "make funanim")
 
all: symbol bounce funanim

symbol: symbol.c 
	gcc symbol.c Graphics/gfx.o -lX11 -lm -o symbol

bounce: bounce.c 
	gcc bounce.c Graphics/gfx.o -lX11 -lm -o bounce

funanim: funanim.c 
	gcc funanim.c Graphics/gfx.o -lX11 -lm -o funanim

clean:
	rm symbol bounce funanim

