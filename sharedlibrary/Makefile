CC = gcc-11
CCFLAGS = -Wall -O

all: lib main main2

.PHONY: lib
lib: library1.so library2.so

.PHONY: clean
clean:
	rm -rf main main2 *.so *.o *~

OBJLIB1 = library1.o
library1.so:$(OBJLIB1)
	$(CC) $(CCFLAGS) -shared $< -o $@

OBJLIB2 = library2.o
library2.so:$(OBJLIB2)
	$(CC) $(CCFLAGS) -shared $< -o $@

OBJS1 = main.o 
main:$(OBJS1) 
	$(CC) $(CCFLAGS) -I./ $< -o $@ ./library1.so

OBJS2 = main2.o 
main2:$(OBJS2) 
	$(CC) $(CCFLAGS) -I./ $< -o $@ ./library1.so ./library2.so
