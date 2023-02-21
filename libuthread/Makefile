lib := libuthread.a
target := queue.o uthread.o context.o sem.o preempt.o
CFLAGS = -g
CFLAGS += -Wall -Werror -Wextra
CC = gcc
Q = @


all: $(lib)

$(lib):	$(target)
	ar rcs $(lib) $(target)

%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(target) $(lib)