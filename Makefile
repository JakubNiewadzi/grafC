a.out: main.o BFS.o czytanie.o generator.o dijkstra.o
	$(CC) $^

main.o: BFS.h czytanie.h generator.h dijkstra.h
BFS.o: czytanie.h BFS.h
czytanie.o: czytanie.h
generator.o: generator.h
dijkstra.o: dijkstra.h