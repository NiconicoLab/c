CC = gcc-10

TARGET = $@
SOURCE = $@.c

all: main

clean:
	rm -rf main *.o *~

TARGET:
	$(CC) -o $(TARGET) $(SOURCE)

main.o: main.c
