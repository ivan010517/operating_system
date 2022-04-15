#include<iostream>
#include<pthread.h>
#include<signal.h>
#include<ctime>
#include<unistd.h>

using namespace std;

#define N       5
#define LEFT        (i+N-1) % N
#define RIGHT       (i+1) % N
#define THINKING    0
#define HUNGRY      1
#define EATING      2

static volatile int keepRunning = 1;
void intHandler(int dummy) {
    keepRunning = 0;
}

class Monitors
{
public:
    Monitors()
    {
        for(int i=0; i<N; i++)
        {
            s[i] = PTHREAD_COND_INITIALIZER;
            s_mutex[i] = PTHREAD_MUTEX_INITIALIZER;
        }
    };
    void think();
    void take_forks(int);
    void eat();
    void put_forks(int);
    int test(int);
    void leave(int);
    void print();
private:
    int state[N];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t s_mutex[N];// = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t s[N];// = PTHREAD_COND_INITIALIZER;
};

Monitors monitor;
void *philosopher(void*);

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

    //sleep(1);
    printf("time\t:ph0\tph1\tph2\tph3\tph4\n");
    for(i=1; keepRunning; i++)
    {
        printf("%d\t:", i);
        monitor.print();
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
    int i = *((int*) data);
    while(keepRunning)
    {
        monitor.think();
        monitor.take_forks(i);
        monitor.eat();
        monitor.put_forks(i);
    }
    monitor.leave(i);
    pthread_exit(NULL);
}


void Monitors::take_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    if(!test(i))
    {
        pthread_mutex_unlock(&mutex);
        //cout << i << " wait\n";
        pthread_cond_wait(&s[i], &s_mutex[i]);
        //cout << i << " eat\n";
    }
    else
        pthread_mutex_unlock(&mutex);
}

void Monitors::put_forks(int i)
{
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

int Monitors::test(int i)
{
    if(state[i] == HUNGRY && state[LEFT]!=EATING && state[RIGHT]!=EATING)
    {
        state[i] = EATING;
        pthread_cond_broadcast(&s[i]);
        pthread_mutex_unlock(&s_mutex[i]);
        return 1;
    }
    return 0;
}

void Monitors::think()
{
    srand(time(NULL));
    int random = rand()%N+1;
    sleep(1);
    return;
}

void Monitors::eat()
{
    srand(time(NULL));
    int random = rand()%N+1;
    sleep(1);
    return;
}

void Monitors::leave(int i)
{
    state[i] = THINKING;
    printf("leave %d\n", i);
}

void Monitors::print()
{
    int j;
    for(j=0; j<N; j++)
        if(state[j]==THINKING)
            printf("think\t");
        else if(state[j]==HUNGRY)
            printf("hungry\t");
        else
            printf("eating\t");
        printf("\n");
}
