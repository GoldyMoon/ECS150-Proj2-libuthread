lib := libuthread.a
CFLAGS = -g
CFLAGS += -Wall -Werror -Wextra
CC = gcc

all: $(lib)

$(lib):	queue.o
	ar rcs $(lib) queue.o

uthread.o: uthread.c
	(CC) $(CFLAGS) -c -o uthread.o uthread.c

queue.o: queue.c
	$(CC) $(CFLAGS) -c -o queue.o queue.c

clean:
	rm -f queue uthread


## TODO: Phase 1