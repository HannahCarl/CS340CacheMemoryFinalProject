#include <stdio.h>
#include <time.h>


int main( int argc, char *argv[] ) {
    clock_t start_t, stop_t;
    unsigned long i;
    char myArray[4000000] = { 'a' };
    for(i = 0; i < 4000000; i++){
        myArray[i] = 'a';
        
    }

    for(i = 0; myArray[i] == 'a'; i++){
        start_t = clock();
        myArray[i];
        stop_t = clock();
        printf("%ld: This is how long that number loop takes: %ld in clock cycles \n", i, stop_t-start_t);

        //dostuff
    }

    return 0;
}