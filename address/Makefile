CC = gcc

TARGET = $@
SOURCE = $@.c

all: main

clean:
	rm -rf main *.o *~

OBJS = main.o 
main: $(OBJS) 

TARGET:
	$(CC) -o $(TARGET) $(SOURCE)

main.o: main.c

