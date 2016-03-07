OPTIMIZE=-O0
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11 -pthread
DEPS = SortedList.h
OBJ = SortedList.o
SOURCES = SortedList.c SortedList.h Makefile

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

sltest: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#check: 

#dist: check lab4-KatherineAspinwallShaliniDangi.tar.gz
lab4-KatherineAspinwallShaliniDangi.tar.gz:
	tar -czf $@ $(SOURCES)

clean:
	rm -f *.o *.so *.so.* sltest lab4-KatherineAspinwallShaliniDangi.tar.gz

