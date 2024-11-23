CC:=g++

all: akinator

akinator: main.o akinator.o tree.o
	$(CC) $^ -o $@

main.o: main.cpp
	$(CC) -c main.cpp

akinator.o: akinator.cpp
	$(CC) -c akinator.cpp

tree.o: tree.cpp
	$(CC) -c tree.cpp

clean:
	rm -rf *.o akinator
