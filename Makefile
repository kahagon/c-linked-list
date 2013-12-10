CC=gcc
CFLAGS=-g -Wall

OBJS=linked-list

linked-list: main.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJS)
