#include<stdio.h>
#include<stdlib.h>
#include"read_command.h"

int read_command(char command[], char *parameters[])
{
    //read input
    char buffer[256];
    char *b = buffer;
    size_t bufsize = 256;
    size_t characters;

    characters = getline(&b, &bufsize, stdin);
    if(characters <= 0)
        return 0;
    int buff_i=0, para_i=0, index=0;
    int flag = 0;
    parameters[index] = malloc(sizeof(char[256]));

    //separate parameters
    while( buffer[buff_i]!='\0' && buffer[buff_i]!='\n')
    {

        if(buffer[buff_i]==' ')
            flag = 1;
        else
        {
            if(flag == 1)
            {
                if(index==0)
                    command[buff_i-1] = '\0';
                parameters[index][para_i-1] = '\0';
                index++;
                para_i = 0;
                parameters[index] = malloc(sizeof(char[256]));
                flag = 0;
            }
            if(index==0)
                command[buff_i] = buffer[buff_i];
            parameters[index][para_i] = buffer[buff_i];
        }

        para_i++;
        buff_i++;
    }
    if(index==0)
        command[para_i] = '\0';
    parameters[index][para_i] = '\0';
    parameters[index+1] = NULL;

    return 1;
}

