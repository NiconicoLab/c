CC = gcc-11
CCFLAGS = -Wall -O

all: main main2

.PHONY: clean
clean:
	rm -rf main main2 *.so *.o *~

OBJS1 = main.o 
main:$(OBJS1) 
	$(CC) $(CCFLAGS) -shared library1.c -o library1.so
	$(CC) $(CCFLAGS) -I./ $< -o $@ ./library1.so

OBJS2 = main2.o 
main2:$(OBJS2) 
	$(CC) $(CCFLAGS) -shared library1.c -o library1.so
	$(CC) $(CCFLAGS) -shared library2.c -o library2.so
	$(CC) $(CCFLAGS) -I./ $< -o $@ ./library1.so ./library2.so
