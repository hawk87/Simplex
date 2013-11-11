#include <stdio.h>

#define ROW 3
#define COLUMN 3

main() {
	
   float **matrix;
   //int i,j;

   /* Diag */
   printf("  matrix: %p\n", matrix);
   printf(" &matrix: %p\n", &matrix);
   printf(" *matrix: %p\n", *matrix);

   /*  
       matrix: 0x5c5ff4
      &matrix: 0xbfac241c
      *matrix: 0x1a4d7c 
   */

	/*for(i = 0; i < RAW; ++i) {
		for(j = 0; j < COLUMN; ++j)
		   printf("%.3f ", matrix[i][j]);
      printf("\n");
   }*/
   return 0;
}
