CC = gcc-11
CCFLAGS = -Wall -O

all: send receive

clean:
	rm -rf send receive *.o *~

OBJS1 = send.o
send:$(OBJS1)
	$(CC) $(CCFLAGS) -o $@ $(OBJS1)


OBJS2 = receive.o
receive:$(OBJS2)
	$(CC) $(CCFLAGS) -o $@ $(OBJS2)

.c.o:
	$(CC) $(CCFLAGS) $(INCLUDE) -c -o $@ $<

send.o: send.c
receive.o: receive.c
