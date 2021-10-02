# Memory allocator

## description
 Memory allocator for GNU/Linux applications which are based on C
 
 **lib** - directory with **allocator** sources files  
 **examples** - directory with user programs for **allocator** testing 
 
  Compiling **allocator** before running any programs from **examples** directory is necessary!
 
 Run **allocator** for appeal internal test function with allocated memory state demonstration  
 Run **time measuring program** for time comparasion between this allocator and standart malloc/free functions

## compilation
  ### allocator
   #### from lib directory
    make dir - create directories
    make/make all - build allocator
    make clean - clean building and executable files
  ### time measuring program
   #### from examples directory 
    make dir - create directories
    make/make all - build time measuring program
    make clean - clean building and executable files
    
## run project
 ### allocator
   #### from lib directory
    ./bin/alloc - run allocator
 ### time measuring program
   #### from examples directory
    ./bin/time_measuring - run time measuring program
    
