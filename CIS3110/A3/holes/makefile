CC = gcc
CFLAGS = -Wall -pedantic -std=c99 -c

holes: program.o
	$(CC) program.o QueueImplementation.o holes.o -o holes

program.o: program.c QueueImplementation.o holes.o
	$(CC) $(CFLAGS) program.c

QueueImplementation.o: QueueImplementation.c QueueInterface.h QueueType.h holes.o
	$(CC) $(CFLAGS) QueueImplementation.c

holes.o: holes.c holes.h 
	$(CC) $(CFLAGS) holes.c

clean:
	rm -rf holes *.o