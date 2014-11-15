all: brasileirinho

brasileirinho: main.o
	cc main.o -o brasileirinho.app

main.o: src/main.c
	cc -c src/main.c
