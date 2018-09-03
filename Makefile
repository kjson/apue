ls:
	gcc -o build/ls src/ls.c -I include/ -L lib/ -lapue -Wall

siso:
	gcc -o build/siso src/siso.c -I include/ -L lib/ -lapue -Wall
