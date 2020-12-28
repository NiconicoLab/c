CXX = g++-10

TARGET = $@
SOURCE = $@.c

all: main

clean:
	rm -rf main *.o *~

TARGET:
	$(CXX) -o $(TARGET) $(SOURCE)

main.o: main.c
