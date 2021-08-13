CC = gcc-11
CCFLAGS = -Wall -O

all: main main2 main3 main4

.PHONY: clean
clean:
	rm -rf main main2 main3 main4 *.o *~

OBJS1 = main.o

main:$(OBJS1)
	$(CC) $(CCFLAGS) -o $@ $(OBJS1)

OBJS2 = main2.o

main2:$(OBJS2)
	$(CC) $(CCFLAGS) -o $@ $(OBJS2)

OBJS3 = main3.o

main3:$(OBJS3)
	$(CC) $(CCFLAGS) -o $@ $(OBJS3)

OBJS4 = main4.o

main4:$(OBJS4)
	$(CC) $(CCFLAGS) -o $@ $(OBJS4)

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

main.o: main.c
main2.o: main2.c
main3.o: main3.c
main4.o: main4.c
