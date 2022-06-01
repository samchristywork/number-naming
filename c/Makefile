CC := gcc

all: build/name_large_numbers

build/name_large_numbers: name_large_numbers.c build/libnum.o
	mkdir -p build/
	${CC} build/libnum.o name_large_numbers.c -o $@

build/libnum.o: libnum.c libnum.h
	mkdir -p build/
	${CC} -c libnum.c -o $@

clean:
	rm -rf build/

