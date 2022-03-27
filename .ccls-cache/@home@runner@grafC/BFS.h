#ifndef _BFS_H_
#define _BFS_H_

typedef struct bfs{
  int* odleglosc;
  int* rodzic;
  int* kolor;
}bfs_t;

void BFS (int ** graf, int wierz, int n, int * ile_sasiadow, bfs_t * output);

#endif