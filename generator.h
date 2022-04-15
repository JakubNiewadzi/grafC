#ifndef _GENERATOR_H_
#define _GENERATOR_H_

#include "czytanie.h"

void wygenerujGraf (graf_t *g, tablice_t *t);
double losuj(double min, double max);
void druk (FILE * plik, graf_t *g);

#endif