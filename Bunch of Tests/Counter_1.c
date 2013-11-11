/* Scansiona la prima riga per determinare il numero di colonne,
poi scansiona SOLO le righe */

#include <stdio.h>

main() {
  
   int c,i,j;
   int rows = 0;
   int columns = 0;
   int sw = 0; 
   
   while((c = getchar()) != EOF) {
      sw = 1;
      if(c == ' ')
         columns++;
      else if(c == '\n') {
         rows++;
         while((c = getchar()) != EOF)
            if(c == '\n')
               rows++;
      }
   }

   if (sw == 1)
      columns++;
   
   /* Diag */

   printf("Rows   : %d\n", rows);
   printf("Columns: %d\n", columns);

return 0;
}
