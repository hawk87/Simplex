/*
Usage:   $gcc -g DynTableauProc.c -o DynTableauProc.out
         $cat TableauInput.lp | ./DynTableauProc.out TableauInput.lp   
*/

// TODO: tableauPurge!

#include <stdio.h>

int countRows(char *filename);
int countColumns(char *filename);
void import(int rows, int columns,float tableau[rows][columns]);
void pivot(int k, int h, int rows, int columns, float tableau[rows][columns]);

main(int argc, char *argv[]) {

   int rows = countRows(argv[1]);
   int columns = countColumns(argv[1]);
   
   printf("Rows   : %d\n", rows);
   printf("Columns: %d\n", columns);
   
   float tableau[rows][columns];

   /* DIAGNOSTICS */

   int i,j;
   int count = 1; // contatore Tableau

   /* Print Tableau */
   printf("\n=== PRINT TABLEAU BEFORE IMPORT [MAIN] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }

   printf("\nTableau Address: %p\n", tableau);

   /* Memory Addresses */
   printf("\n=== MEMORY ADDRESSES BEFORE IMPORT [MAIN]===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\t", i, j, &(tableau[i][j]));
      printf("\n");
   }

   import(rows,columns,tableau);

   /* Memory Addresses */
   printf("\n=== MEMORY ADDRESSES AFTER IMPORT [MAIN]===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\t", i, j, &(tableau[i][j]));
      printf("\n");
   }

   /* Print Tableau */
   printf("\n=== PRINT TABLEAU AFTER IMPORT [MAIN] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }

   /* === SIMPLEX === */

   int unbounded = 0;
   int optimal = 0;

   float theta,ratio;

   int k,h,sw;

   while ((optimal < (columns - 1)) && (unbounded < (rows - 1))) {
      for (j = 1; j < columns; j++)
         if (tableau[0][j] >= 0)
            optimal++;  // se tutti i costi ridotti sono > 0, allora siamo nell'ottimo
         else { // altrimenti scelgo una variabile fuori base con costo ridotto < 0 (Bland)
            optimal = 0;
            h = j; // salvo l'indice della colonna della variabile fuori base scelta
            for (i = 1; i < rows; i++)
               if (tableau[i][h] <= 0) // se ogni riga della colonna della variabile fuori base e' <= 0, allora e' illimitato
                  unbounded++;
               else {
                  unbounded = 0;
                  sw = 0;
                  for (i = 1; i < rows; i++) { // altrimenti calcola i rapporti ed il theta
                     if (tableau[i][h] > 0 && sw == 0) {
                        theta = tableau[i][0] / tableau[i][h];
                        k = i;
                        sw++;
                     }
                     else if (tableau[i][h] > 0) {
                       ratio = tableau[i][0] / tableau[i][h];
                       if (ratio < theta) {
                          theta = ratio;
                          k = i;
                       }
                     }    
                  }
               }
            
            pivot(k, h, rows, columns, tableau);
            
            printf("\n=== PRINT TABLEAU %d ===\n", count++);
            for (i = 0; i < rows; i++) {
               for (j = 0; j < columns; j++)
                  printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
               printf("\n");
            }
         }    
   }

   return 0;
}


void pivot(int k, int h, int rows, int columns, float tableau[rows][columns]) {

   /*
      k = riga del pivot
      h = colonna del pivot
      rows = numero righe tableau
      columns = numero colonne tableau
      tableau = riferimento al tableau
   */
   
   float pivotElem = tableau[k][h];
   int i,j;

   for (j = 0; j < columns; j++)
      tableau[k][j] = tableau[k][j] / pivotElem;
   for (i = 0; i < rows; i++)
      if ((i != k) && (tableau[i][h] != 0)) {
         pivotElem = tableau[i][h];
         for (j = 0; j < columns; j++)
            tableau[i][j] = tableau[i][j] - pivotElem * tableau[k][j];
      }
}



int countRows(char *filename) {

   int c;
   int rows = 0;
   
   FILE *fp = fopen(filename,"r");
   
   while((c = getc(fp)) != EOF)
      if(c == '\n')
         rows++;

   fclose(fp);
   
   return rows;
}



int countColumns(char *filename) {

   int c;
   int columns = 0;
   int sw = 0;
   
   FILE *fp = fopen(filename,"r");
   
   while((c = getc(fp)) != '\n') {
      sw++;
      if(c == ' ')
         columns++;
   }

   fclose(fp);

   if (sw > 0)
      columns++;
   
   return columns;
}



void import(int rows, int columns, float tableau[rows][columns]) {

   int i,j;

   /* Print Init Tableau */
   printf("\n=== INIT TABLEAU [IMPORT] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }

   /* Memory Addresses */
   printf("\n=== MEMORY ADDRESSES [IMPORT] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\t", i, j, &(tableau[i][j]));
      printf("\n");
   }

   /* Tableau Import */
   for(i = 0; i < rows; i++)
  	   for(j = 0; j < columns; j++)
         scanf("%f", &(tableau[i][j]));

   /* Print Tableau */
   printf("\n=== PRINT TABLEAU [IMPORT] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }
}
