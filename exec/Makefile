CC = gcc-11
CCFLAGS = -Wall -O

all: main

.PHONY: clean
clean:
	rm -rf main *.o *~

OBJS1 = main.o

main:$(OBJS1)
	$(CC) $(CCFLAGS) -o $@ $(OBJS1)

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

main.o: main.c
