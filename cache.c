#include <stdio.h>
#include <time.h>

#define ITERATIONS 400000


int main( int argc, char *argv[] ) {
    clock_t start_t, stop_t;
    unsigned long i;
    char myArray[ITERATIONS];
    for(i = 0; i < ITERATIONS; i++){
        myArray[i] = 'a';
        
    }

    for(i = 0; i < ITERATIONS; i++){
        start_t = clock();
        stop_t = clock();
        printf("%ld: This is how long that null access takes: %ld in clock cycles \n", i, stop_t-start_t);

        //dostuff
    }

    return 0;
}