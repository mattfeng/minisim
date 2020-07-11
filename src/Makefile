all: main

clean: main atom.o vec.o
	rm $^

main: main.cpp atom.o vec.o
	g++ -o $@ $^

atom.o: atom.cpp atom.h vec.o
	g++ -c $< -o $@

vec.o: vec.cpp vec.h
	g++ -c $< -o $@

