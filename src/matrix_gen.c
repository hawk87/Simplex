/*
Usage: $gcc -g matrix_gen.c -o matrix_gen.out
$./matrix_gen.out <rows> <columns> <random_range> <../test/filename.lp>
*/

#include <stdio.h>
#include <stdlib.h>

main(int argc, char *argv[]) {

   long i,j = 0;
   char *filename = argv[4];
   long rows = strtoul(argv[1], argv, 10);
   long columns = strtoul(argv[2], argv, 10);

   long random_range = strtoul(argv[3], argv, 10);

   // printf("Rows: %ld\n", rows);
   // printf("Columns: %ld\n", columns);

   int matrix[rows][columns];

	// Fill Matrix
	for (i = 0; i < rows; i++)
		matrix[i][0] = (rand() % random_range) + 1;

	for (i = 0; i < rows; i++)
      for (j = 0; j < columns; j++)
         matrix[i][j] = rand() % random_range;

   // Initial Objective Function
   matrix[0][0] = 0;

   // Reduced Costs
   for (j = 1; j < columns; j = j + j++)
      matrix[0][j] = (-1) * matrix[0][j];

   // Writing the matrix in a file
   FILE *fp;
   fp = fopen(filename,"w");

   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns - 1; j++)
			fprintf(fp, "%d ", matrix[i][j]);

			fprintf(fp, "%d", matrix[i][j]);

    		if(i < rows - 1)
				fprintf(fp, "\n");
   }
   fclose(fp);

   printf("\n[*] File %s written correctly!\n\n", filename);

   /* DIAGNOSTICS

   // Print Matrix
   for (i = 0; i < rows; i++) {
      for (j = 0; j < columns; j++)
         printf("(%ld,%ld): %d\t", i, j, matrix[i][j]);
      printf("\n");
   }
   */
}
