CC = gcc-10

TARGET = $@
SOURCE = $@.c

all: send receive

clean:
	rm -rf send receive *.o *~

OBJS = main.o 
main: $(OBJS) 

TARGET:
	$(CC) -o $(TARGET) $(SOURCE)

send.o: send.c
receive.o: receive.c
