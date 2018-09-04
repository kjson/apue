build-debug:
	gcc -o build/${PROG} src/${PROG}.c -I include/ -L lib/ -lapue -Wall -std=c99 -g

run: build-debug
	./build/${PROG}

.PHONY: build-debug
