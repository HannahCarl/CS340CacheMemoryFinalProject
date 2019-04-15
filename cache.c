#include <stdio.h>
#include <time.h>


int main( int argc, char *argv[] ) {
    clock_t start_t, stop_t;
    unsigned long i;

    start_t = clock();
    for(i = 0; i < 4000000000; i++){
        //dostuff
    }
    stop_t = clock();

    printf("This is how long that number loop takes: %ld \n", (stop_t-start_t)/CLOCKS_PER_SEC);


    return 0;
}