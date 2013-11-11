#include <stdio.h>
#include "simplex.h"

main(int argc, char *argv[]) {

   int rows = countRows(argv[1]);
   int columns = countColumns(argv[1]);
   
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

   simplex(rows, columns, tableau);

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


void import(char *filename, int rows, int columns, float tableau[rows][columns]) {

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
}
