lib := libuthread.a
CFLAGS = -g
CFLAGS += -Wall -Werror -Wextra
CC = gcc

all: $(lib)

$(lib):	queue.o uthread.o context.o sem.o
	ar rcs $(lib) queue.o uthread.o context.o sem.o

context.o: context.c
	$(CC) $(CFLAGS) -c -o context.o context.c

sem.o: sem.c
	$(CC) $(CFLAGS) -c -o sem.o sem.c
	
uthread.o: uthread.c
	$(CC) $(CFLAGS) -c -o uthread.o uthread.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c -o queue.o queue.c

clean:
	rm -f queue.o uthread.o context.o


## TODO: Phase 1
