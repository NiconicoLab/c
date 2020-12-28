CC = gcc-10

TARGET = $@
SOURCE = $@.c

all: send receive

clean:
	rm -rf send receive *.o *~

TARGET:
	$(CC) -o $(TARGET) $(SOURCE)

send.o: send.c
receive.o: receive.c
