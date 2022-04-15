#include"background.h"
#include"strcmp.h"
#include<stdio.h>
#include<stdlib.h>

int background(char *parameters[])
{
    int i;
    char *temp = "&";
    for(i=0; parameters[i]!=NULL; i++)
        if(strcmp(parameters[i], temp) && parameters[i+1]==NULL)
        {
            free(parameters[i]);
            parameters[i] = NULL;
            return 1;
        }
    return 0;
}
