#include "dijkstra.h"

int droga(tablice_t * t, int poczatek, int n){
  double * droga = malloc(n*sizeof(*droga));
  int * poprzednik = malloc(n*sizeof(*poprzednik));
  
  for(int i=0;i<n;i++){
    droga[i]=-1.0;
    poprzednik[i]=-1;
  }
  droga[poczatek]=0;
  
  return 5;
}