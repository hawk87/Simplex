#include <stdio.h>

#define ROW 3
#define COLUMN 3

float matrix[ROW][COLUMN];

main() {
   
   int i,j;

   /* Matrix Initialization */
   printf("Matrix Initialization:\n");
   for(i = 0; i < ROW; i++) {
  	   for(j = 0; j < COLUMN; j++)
  	      printf("%.1f ", matrix[i][j]);
      printf("\n");   
   }
	
   /* Diagnostics */
   for(i = 0; i < ROW; i++)
  	   for(j = 0; j < COLUMN; j++)
         printf("Memory Matrix (%d,%d): %p\n", i, j, &(matrix[i][j]));

   printf("Matrix Address   : %p\n", matrix);
   printf("Size of (int)    : %d bytes\n", sizeof(int));
   printf("Size of (float)  : %d bytes\n", sizeof(float));
   printf("Size of (double) : %d bytes\n", sizeof(double));  
   

   /* Matrix Import */
   for(i = 0; i < ROW; i++)
  	   for(j = 0; j < COLUMN; j++)
         scanf("%f", &(matrix[i][j]));

   /* Print Matrix */
   printf("Matrix:\n");
   for(i = 0; i < ROW; i++) {
  	   for(j = 0; j < COLUMN; j++)
  	      printf("%.1f ", matrix[i][j]);
      printf("\n");
   }

   return 0;
}
