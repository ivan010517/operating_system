#ifndef __MY_MM_H_INCLUDED__
#define __MY_MM_H_INCLUDED__

#include <stddef.h>

void *mymalloc(size_t);
void myfree(void *);
void *myrealloc(void *ptr, size_t );
void *mycalloc(size_t nmemb, size_t );

#endif
