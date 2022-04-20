# Homework Assignment #4
This part requires that you write a memory manager in C. In other words, instead of wrappers as shown below
```
1 #include <stdlib.h>
2 #include "mm.h"
3
4 void *mymalloc(size_t size)
5 {
6 return malloc(size);
7 }
8
9 void myfree(void *ptr)
10 {
11 free(ptr);
12 }
13
14 void *myrealloc(void *ptr, size_t size)
15 {
16 return realloc(ptr, size);
17 }
18
19 void *mycalloc(size_t nmemb, size_t size)
20 {
21 return calloc(nmemb, size);
22 }
```
you are writing your own memory management functions, as follows:
```
1 #include "mm.h"
2
3 void *mymalloc(size_t size)
4 {
5 // your own code
6 }
7
8 void myfree(void *ptr)
9 {
10 // your own code
11 }
12
13 void *myrealloc(void *ptr, size_t size)
14 {
15 // your own code
16 }
17
18 void *mycalloc(size_t nmemb, size_t size)
19 {
20 // your own code
21 }
```
Note that mm.h is as given below.
```
1 #ifndef __MY_MM_H_INCLUDED__
2 #define __MY_MM_H_INCLUDED__
3
4 #include <stddef.h>
3
5
6 void *mymalloc(size_t size);
7 void myfree(void *ptr);
8 void *myrealloc(void *ptr, size_t size);
9 void *mycalloc(size_t nmemb, size_t size);
10
11 #endif
```
For an example, please see pp. 185–189 of The C Programming Language, Second Edition by Kernighan and
Ritchie, Prentice Hall, 1988.

