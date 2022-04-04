grafC: main.o BFS.o czytanie.o generator.o dijkstra.o
	$(CC) -o grafC main.o BFS.o czytanie.o generator.o dijkstra.o

testBFS: testBFS.o BFS.o czytanie.o
	$(CC) -o testBFS testBFS.o BFS.o czytanie.o

testCzytania: testCzytania.o czytanie.o
	$(CC) -o testCzytania testCzytania.c czytanie.o

testDijkstra: testDijkstra.o dijkstra.o czytanie.o
	$(CC) -o testDijkstra testDijkstra.c dijkstra.o czytanie.o

testGeneracji: testGeneracji.o generator.o czytanie.o
	$(CC) -o testGeneracji testGeneracji.o generator.o czytanie.o