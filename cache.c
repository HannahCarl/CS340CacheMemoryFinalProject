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

#define ITERATIONS 5000
#define ITERATIONSCLOCK 100
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
	    median = (results[(size-1)/2] + results[size/2])/2.0;
    }
    //Else if size of array odd
    else{
        median = results[size/2];
    }
    return median;
}


//Method to calculate mode

double getMode(double results[]){

   // printf("Mode called\n");

    double maxFound, temp;
    int i, j;
    int countMax = 0;
    int count =0;


	for(i = 0; i < ITERATIONS; i++){
		count = 0;
 		for(j =0; j < ITERATIONS; j++){

			if(results[j] == results[i]){

				count++;
			}

		}

		if(count > countMax){
			countMax = count;
			maxFound = results[i];
			//printf("Max found: %f\n", maxFound);
		}
	}



    return maxFound;
}


//Method to calculate trimmed mean

long long getTrimmedMean(double results[]){
    long i = ITERATIONS/4;
    long long sum = 0;
    long long average;
    
    for(; i < ITERATIONS*3/4; i++){
        sum += results[i];
    }
    average = sum/(ITERATIONS/2);

    return average;
}



//Method to find cache size
void getCacheSize(){
    struct timespec t1, t2;
    long i, count, position;
    long elapsedTimeFound;
    //long long testSize[] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
             		//1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864, 134217728,
                       // 268435456, 536870912, 1073741824, 2147483648, 4294967296};
    long long testSize[] = {8192, 16384, 32768, 65536, 131072, 262144, 524288};
    long long size;
    double results[ITERATIONS];
    double mode = 0.0;
    double previousMode =0.0;
    char tempChar = 'a';




    //Loop to run through block sizes
    //for(size = 1024; size<= 4294967296; ){
    for(position = 0; position < (sizeof(testSize)/sizeof(long long)); position++){
    for(count = 0; count<= ITERATIONS; count++ ){
        
    size = testSize[position];
	char testArray2[size];


    	//Loop builds array of block size
    	for(i = 0; i < size; i++){
        	testArray2[i] = 'a';
    	}
    
    	//Timing of each cache block size access to a random element
    	clock_gettime(CLOCK_MONOTONIC, &t1);
	tempChar = testArray2[i];
    	testArray2[(i*64) % (size)] +=1;
	testArray2[i] +=1;
	
    	clock_gettime(CLOCK_MONOTONIC, &t2);


    	//Calculate elapsed time
    	elapsedTimeFound = elapsed_ns(&t1, &t2);
        results[count] = elapsedTimeFound;
        

    }
    previousMode = mode;
    mode = getMode(results);

    

    //Output	
    //printf("The mode of cache size %lld access time is %f\n", testSize[position], mode);
   // printf("The trimmed mean of cache size %lld access time is %lld\n", testSize[position], getTrimmedMean(results));

    if(previousMode > 0 && (mode/previousMode) > 1.2){
	printf("The L2 cache size is approximately: %lld bytes\n", testSize[position]/2);
	break;
    }


    }
}


//Method to get cache size
void getCacheBlockSize(){

    struct timespec t1, t2;
    long i, count, position;
    long elapsedTimeFound;
    long long testSize[] = {16,32,64,128,512,1024};
    long long size;
    double results[ITERATIONS];
    double mode = 0.0;
    double previousMode =0.0;


    //Loop to run through block sizes
    //for(size = 1; size<= 4294967296; ){
    for(position = 0; position < 6; position++){
   	 for(count = 0; count<= ITERATIONS; count++ ){
        
    		size = testSize[position];
		char testArray2[size/16];


    	//Loop builds array of block size
    	for(i = 0; i < size/16; i++){
        	testArray2[i] = 'a';
    	}
    
    	//Timing of each cache block size access to a random element
    	clock_gettime(CLOCK_MONOTONIC, &t1);
    	for(i=0; i < size/16; i++){

		testArray2[(i*64) % size] +=1;
	}
    	clock_gettime(CLOCK_MONOTONIC, &t2);


    	//Calculate elapsed time
    	elapsedTimeFound = elapsed_ns(&t1, &t2);
        results[count] = elapsedTimeFound;
        

    }

    previousMode = mode;
    mode = getMode(results);
	//printf("Mode : %f Previous mode: %f\n", mode, previousMode);
	
    //Output	
    //printf("The mode of cache block size %lld access time is %f\n", testSize[position], getMode(results));
    //printf("The trimmed mean of cache block size %lld access time is %lld\n", testSize[position], getTrimmedMean(results));

    if(previousMode >0 && (mode/previousMode) > 1.45 ){
	printf("The cache block size is approximately: %lld bytes\n", testSize[position]);
	break;
    }


    }
	
	



}

//Method to measure time of call clock functions
double getClockTime(){

    struct timespec t1, t2;
    unsigned long i;
    double results[ITERATIONS];
    float sum = 0;
    float average;
    float mode[100];
    float max = 0;
    int position = 0;



    //check getres()
    clock_getres(CLOCK_MONOTONIC, &t1);
    //printf("getres() timing resolution = %ld nsecs\n", t1.tv_nsec);

    //testing clock acces time for an array when only accessing one element ITERATIONS times
    for(i = 0; i < ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &t1);
        clock_gettime(CLOCK_MONOTONIC, &t2);
	
	results[i] = elapsed_ns(&t1, &t2);

    
    }


   
    //printf("the mode of clock time is: %.6f\n", getMode(results));
	return getMode(results);


}

//Method to get time of accessing cache
void getCacheTime(){

   struct timespec t1, t2;
    unsigned long i,j;
    double results[ITERATIONS];
    float sum = 0;
    float average;
    float mode[100];
    float max = 0;
    int position = 0;
    char testArray[] = {'a'};
    char testChar = 'a';
    int runs = 10;
    double clockTime = getClockTime();
    double cacheTime = 0.0;
    double offsetOfCall = 1.0;


   for(i = 0; i < ITERATIONS; i++){
        clock_gettime(CLOCK_MONOTONIC, &t1);

        testArray[0] = testChar + testChar +runs;
	
        clock_gettime(CLOCK_MONOTONIC, &t2);
	//printf("Time %ld\n",elapsed_ns(&t1, &t2));
	results[i] = elapsed_ns(&t1, &t2);

        //sum += results[i];     
    }

    cacheTime = getMode(results) - clockTime + offsetOfCall;
    printf("A reference to cache takes approximately: %.6f ns\n", cacheTime);


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
    getCacheTime();
    //getMainMemoryTime();


    return 0;
}
