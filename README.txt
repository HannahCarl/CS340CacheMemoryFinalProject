# CS340CacheMemoryFinalProject

# Team Members

Jacob Mattox - https://github.com/jacobmattox

Hannah Carl - https://github.com/PoschH  
    
    1. How big is a cache block?
        64 bytes
    2. How big is the cache?
        L2 cache is approximately 262144 bytes
    3. How long does a reference to main memory take to complete?
        Approximately 34 nanoseconds
    4. How long does a reference that can be satisfied from cache take to complete?
        Approximately 2 nanoseconds

Explainations and Methodology
    1. For the first problem, we knew how big the block size should be so we tested arrays of characters of lengths between 2^1 and 
        2^10. We access sudo random positions each time and timed how long the accesses took to execute. We kept track of all the output
        times and found the mode of each power of 2. When we compared the modes of each we determined that the largest gaps were 
        in increments of 64 bytes, thus confirming that the block size is 64 bytes.

    2. We decided to show the output of accessing the L2 cache access because we feel that is the best/easiest to represent in a 
        realistic way through accessing array values. We tested this similarly to how we tested cache block. We created multiple
        arrays of various powers of 2 and tested random accesses timing each and saving those outputs. The modes were then calculated
        and compared to determine at what point the L2 cache fills up and has to go out to the much larger L3. Though there was some
        small amount of variablity (especially depending on how many times in a row we run the program), we consistently saw that 262144
        bytes was the most common number we produced.

    3. To find how long access to main memory takes, we had to create much larger arrays. We tested arrays starting at 2^10 and went
        all the way to 2^32 in size. The most consistent jump in access time came after 4MB of data when access times jumped from less
        than 20ns to over 30ns with 34 being the mode on more than 10k iterations at each power of 2.

    4. To get a close enough approimation of cache access time, we first timed how long it took to run just the clock function. Then
        we only needed to add some array accesses and find the difference in that time and the clock access alone. We found this time
        to consistently be 2 nanoseconds.