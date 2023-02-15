# Target library
lib := libuthread.a
CFLAGS = -g
CFLAGS += -Wall -Werror -Wextra
CC = gcc

all: $(lib)

$(lib):	queue.o
	ar rcs $(lib) queue.o

queue.o: queue.c
	$(CC) $(CFLAGS) -c -o queue.o queue.c

clean:
	rm -f queue


## TODO: Phase 1
