OPTIMIZE=-O0
CC = gcc
CFLAGS = $(OPTIMIZE) -g3 -std=gnu11 -pthread
DEPS = parse.h add.h
OBJ = main.o parse.o add.o
SOURCES = main.c parse.c add.c parse.h add.h Makefile README.md

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

addtest: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

#check: 

#dist: check lab4-KatherineAspinwallShaliniDangi.tar.gz
lab14-KatherineAspinwallShaliniDangi.tar.gz:
	tar -czf $@ $(SOURCES)

clean:
	rm -f *.o *.so *.so.* addtest lab4-KatherineAspinwallShaliniDangi.tar.gz

