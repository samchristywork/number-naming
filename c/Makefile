CC := gcc

all: build/name_large_numbers

build/name_large_numbers: src/name_large_numbers.c build/libnum.o
	mkdir -p build/
	${CC} build/libnum.o src/name_large_numbers.c -o $@

build/libnum.o: src/libnum.c src/libnum.h
	mkdir -p build/
	${CC} -c src/libnum.c -o $@

clean:
	rm -rf build/

