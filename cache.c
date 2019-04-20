// -----------------------------------
// CSCI 340 - Operating Systems
// Spring 2019
// cache.c file
// 
// Final Project
// Hannah Carl & Jacob Mattox
// -----------------------------------

#include <stdio.h>
#include <time.h>

#define ITERATIONS 400000
#define BLOCKS_SIZE 1


//Method returns the elapsed time in seconds
long elapsed_s(struct timespec* t1, struct timespec* t2)
{
   
    
    return t2->tv_sec - t1->tv_sec;
}

//Method returns the elapsed time in nanoseconds
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


//Method to sort array in ascending order

void sortArray(float *arrayPtr, int size){

    int i =0;
    int j = 0;
    int k = 0;

    for(i=0; i < size; i++){

	for(j=0; j< size-1; j++){

		if(arrayPtr[j] > arrayPtr[j+1]){
			k = arrayPtr[j];
			arrayPtr[j] = arrayPtr[j+1];
			arrayPtr[j+1] = k;
		}
	}
    }

}


//Method to calculate median

float getMedian(unsigned long results[], int size){


    float median = 0;

    //If size of array even
    if(size%2 == 0){

	median = (results[size-1/2] + results[size/2])/2.0;

    }
    //Else if size of array odd
    else{
        median = results[size/2];
    }


    return median;

}


//Method to calculate mode

int getMode(unsigned long results[]){

    unsigned long i;
    float mode[100];
    float max = 0;
    int position = 0;
    char testArray[ITERATIONS];


    for(i = 0; i < 100; i++){
        mode[i] = 0;
    }


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

    return position;

}

// -----------------------------------
// TO DO
// -----------------------------------
//Method to calculate trimmed mean

void getTrimmedMean(){

}



//Method to find cache block size
void getCacheBlockSize(){
    struct timespec t1, t2;
    long i;
    long elapsedTimeFound;
    long long size;

    //Loop to run through block sizes
    for(size = 1024; size<= 4294967296; ){
   
	char testArray2[size/1024];

    	//Loop builds array of block size
    	for(i = 0; i < size/1024; i++){
        	testArray2[i] = 'a';
    	}
    
    	//Timing of each cache block size access to a random element
    	clock_gettime(CLOCK_MONOTONIC, &t1);
    	testArray2[(i*64) % size];
    	clock_gettime(CLOCK_MONOTONIC, &t2);


    	//Calculate elapsed time
    	elapsedTimeFound = elapsed_ns(&t1, &t2);

	//Output
        printf("%lld, %lu\n", size/1024, elapsedTimeFound);
        
	//Double size for next round
	size = size *2;		

    }
}

// -----------------------------------
//  TO DO
// -----------------------------------

//Method to get cache size
void getCacheSize(){



}

//Method to measure time of call clock functions
void getClockTime(){

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
        //testArray[1000];
        clock_gettime(CLOCK_MONOTONIC, &t2);
        results[i] = elapsed_ns(&t1, &t2);
        //sum += results[i];     
    }
    //printf("sum when accessing one element over and over %f\n", sum);
    //average = sum/ITERATIONS;

    //printf("Average nanoseconds: %f\n", average);

   
    printf("the mode of clock time is: %d\n", getMode(results));


}

void getCacheTime(){

   struct timespec t1, t2;
    unsigned long i;
    unsigned long results[ITERATIONS];
    float sum = 0;
    float average;
    float mode[100];
    float max = 0;
    int position = 0;
    char testArray[ITERATIONS];

   for(i = 0; i < ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &t1);
        testArray[0] = 'b';
        clock_gettime(CLOCK_MONOTONIC, &t2);
        results[i] = elapsed_ns(&t1, &t2);
        //sum += results[i];     
    }
    //printf("sum when accessing one element over and over %f\n", sum);
   // average = sum/ITERATIONS;

    //printf("Average nanoseconds: %f\n", average);
    //handles mode for clock cycles
   
    printf("the mode of accessing cache is: %d\n", getMode(results));


}



// -----------------------------------
//   To Do
// -----------------------------------
//Method to get time to access main memory
void getMainMemoryTime(){


}


//Main method
int main( int argc, char *argv[] ) {

    
    //Call to methods
    getCacheBlockSize();
    getCacheSize();
    getClockTime();
    getCacheTime();
    getMainMemoryTime();


    return 0;
}
