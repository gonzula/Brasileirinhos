CC=cc
CFLAGS= -std=c11 -Wall


all: brasileirinhos.app

brasileirinhos.app: jsonFormatter.o impressao.o structures.o vector.o list.o refcnt.o str.o htable.o serializable.o main.o binary_file.o file_manager.o campeonato.o
	$(CC) $(CFLAGS) *.o -o brasileirinhos.app

campeonato.o: src/campeonato.c
	$(CC) $(CFLAGS) -c src/campeonato.c

binary_file.o: src/sgbd/binary_file.c
	$(CC) $(CFLAGS) -c src/sgbd/binary_file.c

file_manager.o: src/sgbd/file_manager.c
	$(CC) $(CFLAGS) -c src/sgbd/file_manager.c

list.o: src/structures/list.c
	$(CC) $(CFLAGS) -c src/structures/list.c

htable.o: src/structures/htable.c
	$(CC) $(CFLAGS) -c src/structures/htable.c

refcnt.o: src/structures/refcnt.c
	$(CC) $(CFLAGS) -c src/structures/refcnt.c

src.o: src/structures/src.c
	$(CC) $(CFLAGS) -c src/structures/src.c

serializable.o: src/structures/serializable.c
	$(CC) $(CFLAGS) -c src/structures/serializable.c

impressao.o: src/impressao.c
	$(CC) $(CFLAGS) -c src/impressao.c

vector.o: src/structures/vector.c
	$(CC) $(CFLAGS) -c src/structures/vector.c

structures.o: src/structures/structures.c
	$(CC) $(CFLAGS) -c src/structures/structures.c

jsonFormatter.o: src/structures/jsonFormatter.c
	$(CC) $(CFLAGS) -c src/structures/jsonFormatter.c

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

clean:
	rm -rf *.o
