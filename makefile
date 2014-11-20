CC=cc
CFLAGS= -std=c11 -Wall


all: brasileirinhos.app

brasileirinhos.app: list.o refcnt.o str.o htable.o serializable.o main.o
	$(CC) $(CFLAGS) list.o refcnt.o str.o htable.o serializable.o main.o -o brasileirinhos.app

list.o: src/structures/list.c
	$(CC) $(CFLAGS) -c src/structures/list.c

htable.o: src/structures/htable.c
	$(CC) $(CFLAGS) -c src/structures/htable.c

refcnt.o: src/structures/refcnt.c
	$(CC) $(CFLAGS) -c src/structures/refcnt.c

str.o: src/structures/str.c
	$(CC) $(CFLAGS) -c src/structures/str.c

serializable.o: src/structures/serializable.c
	$(CC) $(CFLAGS) -c src/structures/serializable.c

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

clean:
	rm -rf *.o
