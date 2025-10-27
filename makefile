CC = g++

CFLAGS = -g -Wall

prog: lab_9.o
	$(CC) $(CFLAGS) lab_9.o -o prog

lab_9.o: lab_9.cpp
	$(CC) $(CFLAGS) -c lab_9.cpp
	
clean:
	rm -f *.o prog