runcrossword: words.o crossword.o
	gcc words.o crossword.o -o runcrossword

words.o: words.c words.h
	gcc -c words.c -o words.o

crossword.o: crossword.c words.h
	gcc -c crossword.c -o crossword.o

clean:
	rm *.o
	rm runcrossword