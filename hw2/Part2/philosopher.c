#include"philosopher.h"

void philosopher(int i, int n)
{
    while(1)
    {
        think();
        take_fork(i);
        take_fork( (i+1)%n );
        eat();
        put_fork(i);
        put_fork( (i+1)%n );
    }
}
