#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include"read_command.h"
#include"strcmp.h"
#include"background.h"
#include"pipeline.h"
#include"redirection.h"

int main()
{
    signal(SIGCHLD, SIG_IGN);
    while(1)
    {
        char *parameters[256];
        char command[256];
        int status;

        printf("[myshell]: %s $ ", getcwd(NULL, 0));//type_pormpt(
        if(read_command(command, parameters)==0)
            return 0;

        //exit || quit
        char *exit="exit", *quit="quit";
        if(strcmp(command, exit) || strcmp(command, quit))
            return 0;

        //cd
        char *cd="cd";
        if(strcmp(command, cd))
        {
            chdir(parameters[1]);
            continue;
        }

        //if it contain & than execute background
        int background_or_not = background(parameters);

        //begin fork
        int pid = fork();
        if(pid != 0)
        {
            //Parent code
            if(!background_or_not)
                waitpid(pid, &status, 0);
        }
        else
        {
            //Child code
            //pipeline
            if(!pipeline(parameters) && !redirection(parameters))
            {
                int x=execvp(command, parameters);
                if(x<0)
                {
                    printf("Error!\n");
                    return 0;
                }
            }
        }
        //end fork


        //free
        int i;
        for(i=0; parameters[i]!=NULL; i++)
            free(parameters[i]);
    }
}
