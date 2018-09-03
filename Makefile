build:
	gcc -o build/${PROG} src/${PROG}.c -I include/ -L lib/ -lapue -Wall

run: build
	./build/${PROG}
