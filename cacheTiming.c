#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define ITERATIONS 750000


int main( int argc, char *argv[] ) {

    struct timespec t1, t2;
    unsigned long i;
    unsigned long results[ITERATIONS];
    unsigned long sum = 0;
    unsigned long average;
    unsigned long mode[100];
    unsigned long max = 0;
    int position = 0;

    for(i = 0; i < 100; i++){
        mode[i] = 0;
    }


    clock_getres(CLOCK_MONOTONIC, &t1);
    printf("getres() timing resolution = %ld nsecs\n", t1.tv_nsec);

    //testing clock acces time
    for(i = 0; i < ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &t1);
        clock_gettime(CLOCK_MONOTONIC, &t2);
        results[i] = t2.tv_nsec - t1.tv_nsec;
        sum += results[i];     
    }
    average = sum/ITERATIONS;

    printf("Average cycles: %ld\n", average);

    for(i = 0; i < ITERATIONS; i++){
        if(results[i] < 100)
            mode[results[i]] += 1;
    }
    for(i = 0; i < 100; i++){
        if(max < mode[i]){
            max = mode[i];
            position = i;
        }
    }
    printf("the mode of cycles is: %d\n", position);


    return 0;
}