/*
Usage: $gcc -g Simplex.c -o Simplex.out
$cat <filename>.lp | ./Simplex.out <filename>.lp
*/

// TODO: tableauPurge!

#include <stdio.h>

int countRows(char *filename);
int countColumns(char *filename);
void import(int rows, int columns,float tableau[rows][columns]);
void pivot(int k, int h, int rows, int columns, float tableau[rows][columns]);

main(int argc, char *argv[]) {

   int rows = countRows(argv[1]);
   int columns = countColumns(argv[1]);
   
   printf("Rows : %d\n", rows);
   printf("Columns: %d\n", columns);
   
   float tableau[rows][columns];

   int i,j;
   int count = 1; // tableau counter

   /* DIAGNOSTICS */

/* // Print Tableau
   printf("\n=== PRINT TABLEAU BEFORE IMPORT [MAIN] ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
   printf("\n");
   }

   printf("\nTableau Address: %p\n", tableau);

// Memory Addresses
   printf("\n=== MEMORY ADDRESSES BEFORE IMPORT [MAIN]===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\t", i, j, &(tableau[i][j]));
   printf("\n");
   }
*/
   import(rows,columns,tableau);
/*
// Memory Addresses
   printf("\n=== MEMORY ADDRESSES AFTER IMPORT [MAIN]===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %p\t", i, j, &(tableau[i][j]));
   printf("\n");
   }
*/
   // Print Tableau
   printf("\n=== TABLEAU 0 ===\n");
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%d,%d): %.3f\t", i, j, tableau[i][j]);
      printf("\n");
   }

   /* === SIMPLEX === */

   int unbounded = 0;
   int optimal = 0;

   float theta,ratio;

   int k,h,sw;

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
      printf("\n[*] Optimal Solution Found!\n");

      printf("\n[*] z = %.3f\n", -tableau[0][0]);

      for (j = 1; j < columns; j++) {
         if(tableau[0][j] > 0)
            printf("[*] x%d: 0\n",j);
         else for(i = 1; i < rows; i++)
            if(tableau[i][j] == 1)
               printf("[*] x%d: %.3f\n",j,tableau[i][0]);
      }
      printf("\n");
   }
   else printf("\n[-] Unbounded problem!\n");
   return 0;
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

// TODO: unique method for countRows and countColumns

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



void import(int rows, int columns, float tableau[rows][columns]) {

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
         scanf("%f", &(tableau[i][j]));
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
