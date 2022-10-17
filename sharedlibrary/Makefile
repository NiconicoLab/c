CC = gcc-11
CCFLAGS = -Wall -O

# -Lでリンク時のライブラリ名 -Iでライブラリ名
LDFLAGS = -L./ -I./

all: lib main main2 main3

.PHONY: lib
lib: library1.so library2.so library3.so library4.so

.PHONY: clean
clean:
	rm -rf main main2 main3 *.so *.o *~

OBJLIB1 = library1.o
library1.so:$(OBJLIB1)
	$(CC) $(CCFLAGS) -shared $< -o $@

OBJLIB2 = library2.o
library2.so:$(OBJLIB2)
	$(CC) $(CCFLAGS) -shared $< -o $@

OBJLIB3 = library3.o
library3.so:$(OBJLIB3)
	$(CC) $(CCFLAGS) -shared $< -o $@

OBJLIB4 = library4.o
library4.so:$(OBJLIB4)
	$(CC) $(CCFLAGS) $(LDFLAGS) -shared $< -o $@ -lrary3

# libhoge.soが存在する時-lhogeオプションでリンク
# library1.soの場合は-lrary1となる
OBJS1 = main.o 
main:$(OBJS1) 
	$(CC) $(CCFLAGS) $(LDFLAGS) $< -o $@ -lrary1

OBJS2 = main2.o 
main2:$(OBJS2) 
	$(CC) $(CCFLAGS) $(LDFLAGS) $< -o $@ -lrary1 -lrary2

OBJS3 = main3.o
main3:$(OBJS3)
	$(CC) $(CCFLAGS) $(LDFLAGS) $< -o $@ -lrary3 -lrary4

.c.o:
	$(CC) -c $<
