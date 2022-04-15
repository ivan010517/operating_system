#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    int fd = open("./text.txt", O_RDWR, S_IRUSR | S_IWUSR);
    struct stat sb;

    if(fstat(fd, &sb) == -1)
        perror("couldn't get file size.\n");
    printf("file size is %ld\n", sb.st_size);


    char *file_in_memory = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    int option=0;
    printf("Choose your option:\n");
    printf("1. increase every charactor\n");
    printf("2. decrease every charactor\n");
    printf("3. exit\n");
    while(scanf("%d", &option) && option!=3)
    {
        for(int i=0; i<sb.st_size; i++)
        {
            if(option==1)
                if(file_in_memory[i] >= 32 && file_in_memory[i]<126)
                    file_in_memory[i]++;
            if(option==2)
                if(file_in_memory[i] > 32 && file_in_memory[i]<=126)
                    file_in_memory[i]--;
        }
    }

    munmap(file_in_memory, sb.st_size);
    close(fd);
}
