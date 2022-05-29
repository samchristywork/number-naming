CC := gcc

all: build/name_large_numbers

build/name_large_numbers: name_large_numbers.c
	mkdir -p build/
	${CC} name_large_numbers.c -o $@

clean:
	rm -rf build/

