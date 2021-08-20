CC = gcc-11
CCFLAGS = -Wall -O

all: main

.PHONY: clean
clean:
	rm -rf main *.so *.o *~

OBJS1 = main.o 
main:$(OBJS1) 
	$(CC) $(CCFLAGS) -shared library1.c -o library1.so
	$(CC) $(CCFLAGS) -I./ main.c -o main ./library1.so
