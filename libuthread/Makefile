lib := libuthread.a
CFLAGS = -g
CFLAGS += -Wall -Werror -Wextra
CC = gcc
Q = @


all: $(lib)

$(lib):	queue.o uthread.o context.o sem.o
	ar rcs $(lib) queue.o uthread.o context.o sem.o

%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f queue.o uthread.o context.o sem.o