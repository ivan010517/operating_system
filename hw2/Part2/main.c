#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include <signal.h>

#define N           5
#define LEFT        (i+N-1) % N
#define RIGHT       (i+1) % N
#define THINKING    0
#define HUNGRY      1
#define EATING      2
typedef int semaphore;
int state[N];
semaphore mutex = 1;
semaphore s[N];

void *philosopher(void*);
void take_forks(int);
void put_forks(int);
void test(int);
void think();
void eat();
void up(int*);
void down(int*);
static volatile int keepRunning = 1;
void intHandler(int dummy) {
    keepRunning = 0;
}

int main()
{
    pthread_t t[N];
    int i;

    int arg[N];
    for(i=0; i<N; i++)
    {
        arg[i] = i;
        printf("creat ph%d.\n", i);
        pthread_create(&t[i], NULL, philosopher, &arg[i]);
        //sleep(1);
    }

    signal(SIGINT, intHandler);

    sleep(1);
    printf("time\t:ph0\tph1\tph2\tph3\tph4\n");
    for(i=1; keepRunning; i++)
    {
        printf("%d\t:", i);
        int j;
        for(j=0; j<N; j++)
            if(state[j]==THINKING)
                printf("think\t");
            else if(state[j]==HUNGRY)
                printf("hungry\t");
            else
                printf("eating\t");
        printf("\n");
        //printf("%d\t:%d\t%d\t%d\t%d\t%d\n", i, state[0], state[1], state[2], state[3], state[4]);
        sleep(1);
    }
    for(i=0; i<N; i++)
    {
        pthread_join(t[i], NULL);
    }
    return 0;
}

void *philosopher(void *data)
{
    int *temp = (int*)data;
    int i = *temp;
    //printf("%d %d\n", i, *temp);
    while(keepRunning)
    {
        think();
        take_forks(i);
        eat();
        put_forks(i);
    }
    state[i] = THINKING;
    printf("leave %d\n", i);
    pthread_exit(NULL);
}

void take_forks(int i)
{
    down(&mutex);
    state[i] = HUNGRY;
    test(i);
    up(&mutex);
    down(&s[i]);
}

void put_forks(int i)
{
    down(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    up(&mutex);
}

void test(int i)
{
    if(state[i] == HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
    {
        state[i] = EATING;
        up(&s[i]);
    }
}

void think()
{
    srand(time(NULL));
    int random = rand()%N+1;
    sleep(random);
    return;
}

void eat()
{
    srand(time(NULL));
    int random = rand()%N+1;
    sleep(random);
    return;
}

void up(int *target)
{
    while(*target!=0);
    *target=1;
    return;
}

void down(int *target)
{
    while(*target!=1);
    *target=0;
    return;
}
