Simplex
=======

C Implementation of Simplex Algorithm.

## How to build and run:
    $ make
    $ ./bin/main ./test/Example.lp

## How to delete 'bin' directory:
    $ make clean
    
## How to build and run 'Tableau Generator':
    $ gcc -g ./src/matrix_gen.c -o ./bin/matrix_gen
    $ ./bin/matrix_gen <rows> <columns> <random_range> ./test/<filename>.lp
