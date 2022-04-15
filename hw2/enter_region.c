#include "enter_region.h"

int enter_region(int *lock_ptr)
{
    int old_value;
    do
    {
        old_value = *lock_ptr;
        *lock_ptr = 1;          //means locked
    }while(old_value!=0);

    return 0;
}

int leave_region(int *lock_ptr)
{
    *lock_ptr = 0;
    return 0;
}
