a.out: main.o BFS.o czytanie.o generator.o
	$(CC) $^

main.o: BFS.h czytanie.h generator.h
BFS.o: czytanie.h
czytanie.o: czytanie.h
generator.o: generator.h