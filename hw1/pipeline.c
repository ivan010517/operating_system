#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include"pipeline.h"
#include"strcmp.h"

int pipeline(char *parameters[])
{
    //check pipeline and divide to two process
    int i, flag=0, p2_i=0;
    char *pipeline="|";
    int status;
    char *process1[256], *process2[256];
    for(i=0; parameters[i]!=NULL; i++)
    {
        if(flag)
        {
            process2[p2_i] = parameters[i];
            p2_i++;
        }
        else if(strcmp(parameters[i], pipeline))
        {
            flag = 1;
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
    int fd[2];

    pipe(fd);           //create a pipeline
    int pid = fork();
    if(pid == 0)
    {
    //child process
        close(fd[0]);   //process1 doesn't need to read from pipe
        close(1);       //close std_output, prepare for new standard output
        dup(fd[1]);     //set standard output to fd[1];
        close(fd[1]);   //this file descriptor not needed any more
        execvp(process1[0], process1);
    }
    else
    {
    //parent process
        close(fd[1]);   //process2 doesn't need to write to pipe
        close(0);       //close std_input, prepare for new standard input
        dup(fd[0]);     //set standard input to fd[0]
        close(fd[0]);   //this file descriptor not needed any more
        execvp(process2[0], process2);
    }

    return 1;
}
