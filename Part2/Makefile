OPTIMIZE= -O0
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11 -pthread
DEPS = SortedList.h list.h parse.h
OBJ = SortedList.o list.o parse.o
SOURCES = SortedList.c SortedList.h list.c list.h parse.c parse.h main.c Makefile

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

sltest: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

lab4-part2-KatherineAspinwallShaliniDangi.tar.gz:
	tar -czf $@ $(SOURCES)

clean:
	rm -f *.o *.so *.so.* sltest lab4-part2-KatherineAspinwallShaliniDangi.tar.gz

