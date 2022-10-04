CC = gcc-11
CCFLAGS = -Wall -O

all: main main2

clean:
	rm -rf main main2 *.o *~

OBJS1 = main.o
main:$(OBJS1)
	$(CC) $(CCFLAGS) -o $@ $(OBJS1)

OBJS2 = main2.o
main2:$(OBJS2)
	$(CC) $(CCFLAGS) -o $@ $(OBJS2)

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

main.o: main.c
main2.o: main.c
