//#include<stdio.h>
#include"strcmp.h"

int strcmp(char a[], char b[])
{
    int i;
    for(i=0; a[i]!='\0' || b[i]!='\0'; i++)
        if(a[i] != b[i])
            return 0;
    return 1;
}
