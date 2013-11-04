/* Inserisci 2 procedure, 
   1- conteggio righe e colonne
   2- importazione matrice da file
*/

#include <stdio.h>

main() {
 
   int c,i,j = 0;
   int rows = 0;
   int columns = 0;
   int sw = 0;
   
   FILE *fp = fopen("MatrixInput.lp","r");
   
   while((c = getc(fp)) != EOF) {
      sw++;
      if(c == ' ')
         columns++;
      else if(c == '\n') {
         rows++;
         while((c = getc(fp)) != EOF)
            if(c == '\n')
               rows++;
      }
   }

   fclose(fp);

   if (sw > 0)
      columns++;
   
   /* DIAG */

   printf("Rows   : %d\n", rows);
   printf("Columns: %d\n", columns);

   /* ============================ */

   float matrix[rows][columns];

   /* Print Init Matrix */
   printf("\n=== INIT MATRIX ===\n");
   for (i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.1f\n", i, j, matrix[i][j]);

   /* Memory Addresses */
   printf("\n=== MEMORY ADDRESSES ===\n");
   for (i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\n", i, j, &(matrix[i][j]));

   /* Matrix Import */
   for(i = 0; i < rows; i++)
  	   for(j = 0; j < columns; j++)
         scanf("%f", &(matrix[i][j]));

   /* Print Matrix */
   printf("\n=== PRINT MATRIX ===\n");
   for (i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.1f\n", i, j, matrix[i][j]);

return 0;
}
