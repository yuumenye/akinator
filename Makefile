CC:=g++

all: akinator

akinator: main.o akinator.o tree.o draw.o stack.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) -c main.cpp

akinator.o: akinator.cpp
	$(CC) -c akinator.cpp

tree.o: tree.cpp
	$(CC) -c tree.cpp

draw.o: draw.cpp
	$(CC) -c draw.cpp

stack.o: stack.cpp
	$(CC) -c stack.cpp

clean:
	rm -rf *.o akinator
