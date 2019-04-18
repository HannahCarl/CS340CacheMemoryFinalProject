#include <stdio.h>
#include <time.h>

#define ITERATIONS 400000
#define BLOCKS_SIZE 1

long elapsed_ns(struct timespec* t1, struct timespec* t2)
{
  long seconds = t2->tv_sec - t1->tv_sec; 
  long ns = t2->tv_nsec - t1->tv_nsec; 
    
  if (ns < 0) { // clock underflow 
    --seconds;
    ns += 1000000000; 
  }

  return seconds*1000000000 + ns;
}



int main( int argc, char *argv[] ) {

    struct timespec t1, t2;
    unsigned long i;
    unsigned long results[ITERATIONS];
    float sum = 0;
    float average;
    float mode[100];
    float max = 0;
    int position = 0;
    char testArray[ITERATIONS];

    for(i = 0; i < 100; i++){
        mode[i] = 0;
    }
    for(i = 0; i < ITERATIONS; i++){
        testArray[ITERATIONS] = 'a';
    }

    //not actually an error
    clock_getres(CLOCK_MONOTONIC, &t1);
    printf("getres() timing resolution = %ld nsecs\n", t1.tv_nsec);

    //testing clock acces time for an array when only accessing one element ITERATIONS times
    for(i = 0; i < ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &t1);
        testArray[1000];
        clock_gettime(CLOCK_MONOTONIC, &t2);
        results[i] = elapsed_ns(&t1, &t2);
        sum += results[i];     
    }
    printf("sum when accessing one element over and over %f\n", sum);
    average = sum/ITERATIONS;

    printf("Average cycles: %f\n", average);
    //handles mode for clock cycles
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



    //access main memory at different locations based on BLOCKS_SIZE
    for(i = 0; i < ITERATIONS; i+=BLOCKS_SIZE){
        clock_gettime(CLOCK_MONOTONIC, &t1);
        testArray[i];
        clock_gettime(CLOCK_MONOTONIC, &t2);
        results[i] = elapsed_ns(&t1, &t2);
        sum += results[i];     
    }

    printf("sum is %f\n", sum);
    average = sum/(ITERATIONS/BLOCKS_SIZE);

    printf("Average main memory access cycles: %f\n", average);

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
    printf("the mode of main memory access cycles is: %d\n", position);

    return 0;
}