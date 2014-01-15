/* Two Phases Method */

#include <stdio.h>
#include "simplex.h"

#define EPSILON 0.000001

int twoPhases(int rows, int new_columns, float new_tableau[rows][new_columns]) {

   int i,j;

   // Building artificial variables
   float objFunc[new_columns];

   for (j = 0; j < new_columns; j++) // saving the objective function
      objFunc[j] = new_tableau[0][j];

   for (j = 0; j < new_columns-rows+1; j++) // preparing the 1st row with zeros..
      new_tableau[0][j] = 0;

   for (j = new_columns-rows+1; j < new_columns; j++) // .. and ones
      new_tableau[0][j] = 1;

   i = 1;
   for (j = new_columns-rows+1; j < new_columns; j++) // identity matrix
         new_tableau[i++][j] = 1;

   // Print new_tableau
   printf("\n=== PRINT TABLEAU [ID MATRIX] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < new_columns; j++)
         printf("(%d,%d): %.3f\t", i, j, new_tableau[i][j]);
      printf("\n");
   }

   for (i = 1; i < rows; i++) // subtracting the other rows from 0th row 
      for (j = 0; j < new_columns; j++)
         new_tableau[0][j] = new_tableau[0][j] - new_tableau[i][j];

   // Print new_tableau
   printf("\n=== PRINT TABLEAU [1st PHASE] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < new_columns; j++)
         printf("(%d,%d): %.3f\t", i, j, new_tableau[i][j]);
      printf("\n");
   }

   /* === SIMPLEX PHASE 1 === */
   simplex(rows, new_columns, new_tableau);
   
   if(new_tableau[0][0] < 0 - EPSILON) {
      printf("[#] Unfeasible problem!\n\n");
      return 1;
   }
   else {
      for (j = 0; j < new_columns; j++)
         new_tableau[0][j] = objFunc[j];

      printf("\n=== PRINT TABLEAU [w -> z] ===\n");
      for (i = 0; i < rows; i++) {
         for (j = 0; j < new_columns-rows+1; j++)
            printf("(%d,%d): %.3f\t", i, j, new_tableau[i][j]);
         printf("\n");
      }

      // check for adjusting
      for (j = 1; j < new_columns-rows+1; j++)
          if(new_tableau[0][j] != 0)
             for (i = 1; i < rows; i++)
                 if (new_tableau[i][j] == 1)
                     pivot(i, j, rows, new_columns, new_tableau);
      return 0;
   }
}
