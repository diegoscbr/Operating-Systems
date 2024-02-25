CC = gcc
CFLAGS = -Wall -Wextra

histList.o: histList.c histList.h
	$(CC) $(CFLAGS) -c histList.c


gush: gush.c histList.o
	$(CC) $(CFLAGS) gush.c histList.o -o gush


.PHONY: clean

clean:
	rm -f gush histList.o
