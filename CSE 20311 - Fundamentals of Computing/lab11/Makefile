all: project

project: project.o utils.o
	gcc -o project project.o utils.o

project.o: project.c utils.h
	gcc -c project.c

utils.o: utils.c utils.h
	gcc -c utils.c


clean:
	rm -f *.o project