/* Scansiona tutto */

#include <stdio.h>

main() {
  
   int c;
   float rows = 0;
   float columns = 0;
   
   while((c = getchar()) != EOF) {
      if(c == ' ')
         columns++;
      if(c == '\n') {
         rows++;
         columns++;
        }
   }

   float colOverRows = columns / rows;

   /* Diag */

   printf("Rows       : %.1f\n",rows);
   printf("Columns    : %.1f\n",columns);

   printf("File has %.1f rows and %.1f columns.\n", rows, colOverRows);

return 0;
}
