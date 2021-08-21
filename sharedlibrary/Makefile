CC = gcc-11
CCFLAGS = -Wall -O

# -Lでリンク時のライブラリ名 -Iでライブラリ名
LDFLAGS = -L./ -I./

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

# libhoge.soが存在する時-lhogeオプションでリンク
# library1.soの場合は-lrary1となる
OBJS1 = main.o 
main:$(OBJS1) 
	$(CC) $(CCFLAGS) $(LDFLAGS) $< -o $@ -lrary1

OBJS2 = main2.o 
main2:$(OBJS2) 
	$(CC) $(CCFLAGS) $(LDFLAGS) $< -o $@ -lrary1 -lrary2
