#include <stdio.h>
#include "simplex.h"

int main(int argc, char *argv[]) {

   int rows = countRows(argv[1]);
   int columns = countColumns(argv[1]);

   printf("Opening %s\n", argv[1]);
   
   printf("Rows : %d\n", rows);
   printf("Columns: %d\n", columns);
   
   float tableau[rows][columns];

   int i,j;
/*
   // Print Tableau
   printf("\n=== PRINT TABLEAU BEFORE IMPORT [MAIN] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
   printf("\n");
   }
*/
   import(argv[1], rows, columns, tableau);

   // Print Init Tableau
   printf("\n=== TABLEAU 0 ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }

   int new_columns = columns+rows-1;

   float new_tableau[rows][new_columns];

   copyTableau(rows, columns, tableau, new_tableau);

   // Print Init Tableau
   printf("\n=== TABLEAU [COPY] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < new_columns; j++)
         printf("(%d,%d): %.3f\t", i, j, new_tableau[i][j]);
      printf("\n");
   }

   twoPhases(rows, new_columns, new_tableau);

   printf("\n=== TABLEAU [AFTER TWO PHASES] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, new_tableau[i][j]);
      printf("\n");
   }

   // copia tableau on the fly
   for(i = 0; i < rows; i++)
       for(j = 0; j < columns; j++)
           tableau[i][j] = new_tableau[i][j];

   simplex(rows, columns, tableau); // e' sbagliato che il secondo argomento sia columns, mentre new_tableau e' [rows][new_columns]

   return 0;
}

// TODO: CHECK
int countRows(char *filename) {

   int c;
   int rows = 1;
   
   FILE *fp = fopen(filename,"r");
   
   while((c = getc(fp)) != EOF)
      if(c == '\n')
         rows++;

   fclose(fp);
   
   return rows;
}

// TODO: CHECK
int countColumns(char *filename) {

   int c;
   int columns = 1;
   
   FILE *fp = fopen(filename,"r");
   
   while((c = getc(fp)) != '\n') {
      if(c == ' ')
         columns++;
   }

   fclose(fp);
   
   return columns;
}

int import(char *filename, int rows, int columns, float tableau[rows][columns]) {

   FILE *fp = fopen(filename,"r");   

   int i,j;
/*
   // Print Init Tableau
   printf("\n=== INIT TABLEAU [IMPORT] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }

   // Memory Addresses
   printf("\n=== MEMORY ADDRESSES [IMPORT] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\t", i, j, &(tableau[i][j]));
      printf("\n");
   }
*/
   // Tableau Import
   for(i = 0; i < rows; i++)
           for(j = 0; j < columns; j++)
         fscanf(fp, "%f", &(tableau[i][j]));
/*
   // Print Tableau
   printf("\n=== PRINT TABLEAU [IMPORT] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
   printf("\n");
   }
*/
   return 0;
}

int copyTableau(int rows, int columns, float tableau[rows][columns], float new_tableau[rows][columns+rows-1]) {

   int i,j;

   for(i = 0; i < rows; i++) {
      for(j = 0; j < columns+rows-1; j++)
          new_tableau[i][j] = tableau[i][j];
      for (j = columns; j < columns+rows-1; j++)
          new_tableau[i][j] = 0;
   }

   return 0;
}
