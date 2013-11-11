#include <stdio.h>
#define _MAX_ 2

main(int argc, char *argv[]) {

   int i,j;
   int rc[_MAX_];
/*
   printf("rc: %p\n\n", rc);
   
   // Indirizzi
   for (i = 0; i < _MAX_; i++)
      printf("&rc[%d]: %p\n", i, &rc[i]);
*/
   // Contenuti
   for (i = 0; i < _MAX_; i++)
      printf("rc[%d]: %d\n", i, rc[i]);

   count_RC(argv[1], rc);

   // Contenuti
   for (i = 0; i < _MAX_; i++)
      printf("rc[%d]: %d\n", i, rc[i]);

/*
   // Indirizzi
   printf("\npointer  : %p\n", pointer);
   printf("pointer+%d: %p\n\n",'\x01', pointer + '\x01');

   // Contenuti
   printf("*pointer  : %d\n", *pointer);
   printf("*pointer+%d: %d\n\n", '\x01',*(pointer + '\x01'));
*/

//   int pointer = count_RC(argv[1], rc);
//   printf(" pointer: %p\n", pointer);
//   printf("*pointer: %p\n", pointer);

   int rows = rc[0];
   int columns = rc[1];
   
   printf("Rows   : %d\n", rows);
   printf("Columns: %d\n", columns);
   
   float tableau[rows][columns];

   // Print Tableau
   printf("\n=== PRINT TABLEAU ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }
}


int count_RC(char *filename, int rowsCol[_MAX_]) {

   int c;
   int sw = 0;

   rowsCol[0] = 0; // # rows
   rowsCol[1] = 0; // # columns
   
   FILE *fp = fopen(filename,"r");

   if ((c = getc(fp)) == EOF) { // empty file
      fclose(fp);
      return 0;
   }

   else {
      while((c = getc(fp)) != '\n') {
         sw++;
         if(c == ' ')
            rowsCol[1]++;
      }

      if (sw > 0) {
         rowsCol[0]++;
         rowsCol[1]++;      
      }

      while((c = getc(fp)) != EOF) {
         if(c == '\n')
            rowsCol[0]++;
      }
   }

   fclose(fp);
   
   return 0;
}
