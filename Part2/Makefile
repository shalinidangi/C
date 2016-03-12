OPTIMIZE= -O0
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11 -pthread -lrt
DEPS = SortedList.h list.h parse.h
OBJ = SortedList.o list.o parse.o main.o
SOURCES = SortedList.c SortedList.h list.c list.h parse.c parse.h main.c p2_answers.txt graphs_part2.pdf Makefile

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

sltest: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

dist: lab4-part2-KatherineAspinwallShaliniDangi.tar.gz
lab4-part2-KatherineAspinwallShaliniDangi.tar.gz:
	tar -czf $@ $(SOURCES)

clean:
	rm -f *.o *.so *.so.* sltest lab4-part2-KatherineAspinwallShaliniDangi.tar.gz

