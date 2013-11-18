/* === SIMPLEX === */

#include <stdio.h>
#include "simplex.h"

void simplex(int rows, int columns, float tableau[rows][columns]) {

   int unbounded = 0;
   int optimal = 0;

   float theta,ratio;

   int i,j = 0;
   int h,k = 0;
   int sw = 0;

   int count = 0;

   while ((optimal < (columns - 1)) && (unbounded < (rows - 1))) {
      for (j = 1; j < columns; j++)
         if (tableau[0][j] >= 0)
            optimal++;
         else {
            optimal = 0;
            h = j;
            for (i = 1; i < rows; i++)
               if (tableau[i][h] <= 0)
                  unbounded++;
               else {
                  unbounded = 0;
                  sw = 0;
                  for (i = 1; i < rows; i++) {
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
            
            printf("\n=== TABLEAU %d ===\n", count++);
            for (i = 0; i < rows; i++) {
               for (j = 0; j < columns; j++)
                  printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
               printf("\n");
            }
         }
   }
   
   if(optimal == (columns - 1)) {
      
      // Print Optimal Solution
      printf("\n[*] Optimal solution found!\n");

      printf("\n[*] z = %.3f\n", -tableau[0][0]);

      for (j = 1; j < columns; j++) {
         if(tableau[0][j] > 0)
            printf("[*] x%d: 0\n",j);
         else {
            for(i = 1; i < rows; i++)
               if(tableau[i][j] == 1) {
                  printf("[*] x%d: %.3f\n",j,tableau[i][0]);
                  break;
               }
            if (i == rows)
               printf("[*] x%d: 0\n",j);
         }
      }
      printf("\n");
   }
   else printf("[-] Unbounded problem!\n");
   return;
}

void pivot(int k, int h, int rows, int columns, float tableau[rows][columns]) {

   /*
      k = pivot's row
      h = pivot's columns
      rows = tableau's # rows
      columns = tableaus' # columns
      tableau = tableau pointer
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
