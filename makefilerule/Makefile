CC = gcc-11
CCFLAGS = -Wall -O

#.PHONY: all
all: main

.PHONY: clean
clean:
	rm -rf main *.o *~

OBJS1 = main.o 
main:$(OBJS1) 
	$(CC) $(CCFLAGS) $< -o $@

.c.o:
	$(CC) -c $<
