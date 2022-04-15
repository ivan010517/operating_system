#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include<sys/wait.h>
#include"redirection.h"
#include"strcmp.h"

int redirection(char *parameters[])
{
    //check pipeline and divide to two process
    int i, flag=0, p2_i=0;
    char *input="<", *output=">";
    int status;
    char *process1[256], *process2[256];
    for(i=0; parameters[i]!=NULL; i++)
    {
        if(flag)
        {
            process2[p2_i] = parameters[i];
            p2_i++;
        }
        else if(strcmp(parameters[i], input))
        {
            flag = 1;
            process1[i] = NULL;
        }
        else if(strcmp(parameters[i], output))
        {
            flag = 2;
            process1[i] = NULL;
        }
        else
        {
            process1[i] = parameters[i];
        }
    }
    process2[p2_i] = NULL;

    //no pipeline
    if(flag==0)
        return 0;

    //has pipeline
    int fd;

    if(flag==2)
    {
    //write
        fd = open(process2[0], O_WRONLY | O_CREAT, 0644);
        if(fd==0)
        {
            printf("Can't not open: %s\n", process2[0]);
            return 1;
        }
        close(1);       //close std_output, prepare for new standard output
        dup(fd);     //set standard output to fd[1];
        close(fd);   //this file descriptor not needed any more
        execvp(process1[0], process1);
    }
    else
    {
    //read
        fd = open(process2[0], O_RDONLY);
        if(fd==0)
        {
            printf("Can't not open: %s\n", process2[0]);
            return 1;
        }
        close(0);       //close std_input, prepare for new standard input
        dup(fd);     //set standard input to fd[0]
        close(fd);   //this file descriptor not needed any more
        execvp(process1[0], process1);
    }

    return 1;
}
