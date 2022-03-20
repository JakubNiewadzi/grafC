#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#include "czytanie.h"


int grafWTablice (graf_t *g, tablice_t *t, char *plik ) {  /*pobieram wskaźnik na plik, wskaźnik na strókturę oraz nazwę pliku z którego czytam dane */
    
  char c;
  char poprzedniZnak;
  int aktualnyWezel, aktualnySasiad, licznikSasiadow;
  double waga;
  FILE *p = fopen (plik, "r");

  if(p == NULL) {
    printf("Program nie ma dostępu do plik z którego chcesz pobrać dane na temat opisu grafu, spróbuj podać inny plik.\n");
    return 1;
  }
  
  FILE *kp = fopen (plik, "r");        /*plik pomocniczy do określenia ilosci punktów w wierszu */


  if(fscanf(p,"%d %d", &(g->wiersze), &(g->kolumny)) != 2) {
    printf("Nieodpowiedni format lub ilość liczb w pierwszym wierszu pliku!\nPowinny być to 2 liczby naturalne określające liczbę wierszy i kolumn grafu\n");
    return 1;        /*błąd związany z nie podaniem odpowiedniej ilości wierszy i kolumn*/
  }

  fscanf(kp,"%d %d", &(g->wiersze), &(g->kolumny));

  g->macierzSasiedztwa = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    g->macierzSasiedztwa [i] = malloc(g->kolumny * g->wiersze * sizeof *g->macierzSasiedztwa);
  }

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < g->kolumny * g->wiersze; j++) {
      g->macierzSasiedztwa [i] [j] = DBL_MIN;
    }
  }

  t->grafD = malloc(g->kolumny * g->wiersze * sizeof *t->grafD);

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->grafD [i] = malloc(4 * sizeof *t->grafD[i]);
  }

  /* printf("Zaalokowano pamięć na grafD\n"); */

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    for(int j = 0; j < 4; j++) {
      t->grafD [i] [j] = DBL_MIN;
    }
  }

  /* printf("Wypełniono grafD\n"); */

  t->grafBFS = malloc(g->kolumny * g->wiersze * sizeof *t->grafBFS);

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->grafBFS [i] = malloc(g->kolumny * g->wiersze * sizeof *t->grafBFS[i]);
  }

  /* printf("Zaalokowano pamięć na grafBFS\n"); */

  t->sasiedzi = malloc(g->kolumny * g->wiersze * sizeof *t->sasiedzi);

  /* printf("Zaalokowano pamięć na sasiedzi\n"); */

  for(int i = 0; i < g->kolumny * g->wiersze; i++) {
    t->sasiedzi [i] = 0;
  }

  /* printf("Wypełniono sasiedzi\n"); */

  while(c != '\n') {
    c = fgetc(kp);
  }

  aktualnyWezel = 0;
  licznikSasiadow = 0;
  poprzedniZnak = c;

  while(c != EOF) {     /* przelatuje kopie pliku sprawdzajac ile jest zapisanych połączeń w jednym wierszu dodatkow wypełniając tablice sasiedzi*/
    c = fgetc(kp);

    if(c == ' ') {
      if(isalnum(poprzedniZnak) == 8) {
        licznikSasiadow ++;
      }
    }

    if(c == '\n' || c == EOF) {
      licznikSasiadow ++;
      licznikSasiadow = licznikSasiadow / 2;
      t->sasiedzi [aktualnyWezel] = licznikSasiadow;
      /* printf("aktualny wezeł %d ma %d sąsiadów\n", aktualnyWezel, g->sasiedzi [aktualnyWezel]); */
      aktualnyWezel++;
      licznikSasiadow = 0;
    }

    poprzedniZnak = c;
  }

  aktualnyWezel = 0;
  licznikSasiadow = 0;

  while(fscanf(p,"%d :%lf", &aktualnySasiad, &waga) == 2) {    /* główna pętla zapisująca odpowiednie dane w tablicach grafD i grafBFS */

    licznikSasiadow ++;

    if(t->sasiedzi[aktualnyWezel] < licznikSasiadow) {
      aktualnyWezel ++;
      licznikSasiadow = 1;
    }

    /*
    printf("\t\taktualnyWezel = %d, aktualnySasiad = %d, waga = %lf\n", aktualnyWezel, aktualnySasiad, waga);
    printf("\t\tsasiedzi[%d] = %d, licznikSasiadow = %d\n", aktualnyWezel, t->sasiedzi[aktualnyWezel], licznikSasiadow);
    */

    if(aktualnySasiad == aktualnyWezel - 1) {
      t->grafD [aktualnyWezel] [0] = waga;
      t->grafBFS [aktualnyWezel] [licznikSasiadow] = aktualnySasiad;
      g->macierzSasiedztwa [aktualnyWezel] [aktualnySasiad] = waga;

      /*
      printf("\nDla wezła %d i sąsiada %d przypisano:", aktualnyWezel, aktualnySasiad);
      printf("\n\tgrafD [%d] [0] = %lf", aktualnyWezel, t->grafD [aktualnyWezel] [0]);
      printf("\n\tgrafBFS [%d] [%d] = %d\n", aktualnyWezel, licznikSasiadow, t->grafBFS [aktualnyWezel] [licznikSasiadow]);
      printf("\n\macierzSasiedztwa [%d] [%d] = %lf\n", aktualnyWezel, aktualnySasiad, waga);
      */

    } else if(aktualnySasiad == aktualnyWezel + g->wiersze) {
      t->grafD [aktualnyWezel] [1] = waga;
      t->grafBFS [aktualnyWezel] [licznikSasiadow] = aktualnySasiad;
      g->macierzSasiedztwa [aktualnyWezel] [aktualnySasiad] = waga;

      /*
      printf("\nDla wezła %d i sąsiada %d przypisano:", aktualnyWezel, aktualnySasiad);
      printf("\n\tgrafD [%d] [1] = %lf", aktualnyWezel, t->grafD [aktualnyWezel] [1]);
      printf("\n\tgrafBFS [%d] [%d] = %d\n", aktualnyWezel, licznikSasiadow, t->grafBFS [aktualnyWezel] [licznikSasiadow]);
      printf("\n\macierzSasiedztwa [%d] [%d] = %lf\n", aktualnyWezel, aktualnySasiad, waga);
      */

    } else if(aktualnySasiad == aktualnyWezel + 1) {
      t->grafD [aktualnyWezel] [2] = waga;
      t->grafBFS [aktualnyWezel] [licznikSasiadow] = aktualnySasiad;
      g->macierzSasiedztwa [aktualnyWezel] [aktualnySasiad] = waga;

      /*
      printf("\nDla wezła %d i sąsiada %d przypisano:", aktualnyWezel, aktualnySasiad);
      printf("\n\tgrafD [%d] [2] = %lf", aktualnyWezel, t->grafD [aktualnyWezel] [2]);
      printf("\n\tgrafBFS [%d] [%d] = %d\n", aktualnyWezel, licznikSasiadow, t->grafBFS [aktualnyWezel] [licznikSasiadow]);
      printf("\n\macierzSasiedztwa [%d] [%d] = %lf\n", aktualnyWezel, aktualnySasiad, waga);
      */

    } else if(aktualnySasiad == aktualnyWezel - g->wiersze) {
      t->grafD [aktualnyWezel] [3] = waga;
      t->grafBFS [aktualnyWezel] [licznikSasiadow] = aktualnySasiad;
      g->macierzSasiedztwa [aktualnyWezel] [aktualnySasiad] = waga;

      /*
      printf("\nDla wezła %d i sąsiada %d przypisano:", aktualnyWezel, aktualnySasiad);
      printf("\n\tgrafD [%d] [3] = %lf", aktualnyWezel, t->grafD [aktualnyWezel] [3]);
      printf("\n\tgrafBFS [%d] [%d] = %d\n", aktualnyWezel, licznikSasiadow, t->grafBFS [aktualnyWezel] [licznikSasiadow]);
      printf("\n\macierzSasiedztwa [%d] [%d] = %lf\n", aktualnyWezel, aktualnySasiad, waga);
      */

    } else {
      printf("Żle sformułowany plik! Węzeł nr. %d nie może sąsiadować z węzłem nr. %d!\n", aktualnyWezel, aktualnySasiad);
      t->grafBFS [aktualnyWezel] [licznikSasiadow] = aktualnySasiad;
      g->macierzSasiedztwa [aktualnyWezel] [aktualnySasiad] = waga;
      /*return 1;        błąd związany z podaniem nie odpowowiednich wierzchołków jako sąsiadów*/
    }

  }

  /*printf("\n"); */

  fclose(p);
  fclose(kp);
  return 0;
}
