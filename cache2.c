//CS 340 Project
//Team: Jacob Mattox and Hannah Carl

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>

#define CLOCK_PRECISION 1000000000L



int main( int argc, char *argv[] ) {
    clock_t start_t, stop_t;
    double timeElapsed;
    struct timeval start, end;
    long mtime, secs, usecs;
    unsigned long long i;
    struct timespec t1, t2;
    int counter =0;
    unsigned long currentTimeDifference;
    double elapsedTime[10000];
    char myArray[8000000] = { 'a' };
    for(i = 0; i < 8000000; i++){
        myArray[i] = 'a'+i;
        
    }
    

    for(i = 0; i < 1000000000; i++){
        i+=8000;
        start_t = clock();
        //struct timespec requestStart, requestEnd;
        //clock_gettime(CLOCK_REALTIME, &requestStart);
        myArray[i%(sizeof(myArray))];
        //myArray[0];
        //clock_gettime(CLOCK_REALTIME, &requestEnd);
        stop_t = clock();
        //double accum = ( (double) (requestEnd.tv_sec - requestStart.tv_sec) )+ ((double) (requestEnd.tv_nsec - requestStart.tv_nsec) ) / CLOCK_PRECISION;
        
        //unsigned long timeSpent = seconds*1000000000 + ns;
        timeElapsed = (double) ((stop_t-start_t)* 1000.0) / CLOCKS_PER_SEC;
        //printf("%ld: This is how long that number loop takes: %f \n", i, timeElapsed);
        //printf("%llu: This is how long that number loop takes: %ld in clock cycles \n", i, stop_t-start_t);
        //currentTimeDifference = stop_t-start_t;
        if( counter < 10000){
            if(timeElapsed > 0){
                //printf("%f\n", timeElapsed);
                //printf("%d\n", counter);
                elapsedTime[counter] = timeElapsed;
                counter++;
                
            }
        }
        //printf("%lu\n", stop_t-start_t);
        //i = i*2;

        //dostuff
    }
    for(int i = 0; i < 10000; i++){
        printf("%f at %d\n", elapsedTime[i],i);
    }

    return 0;
}
