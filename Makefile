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

test: testGeneracji testDijkstra testCzytania testBFS
	./testBFS test1 0 wynikiTestuBFS
	./testGeneracji 10 10 0 10 wynikiTestuGeneracji
	./testCzytania test1 3 3 0.485 10.0 wynikiTestuCzytania
	./testDijkstra test1 0 6 11.748 wynikiTestuDijkstra
	diff poprawnyWynikBFS wynikiTestuBFS
	diff poprawnyWynikCzytania wynikiTestuCzytania
	diff poprawnyWynikGeneracji wynikiTestuGeneracji
	diff poprawnyWynikDijkstra wynikiTestuDijkstra