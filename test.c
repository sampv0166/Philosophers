#include "philo.h"

int main ()
{
    struct timeval tv;
    long res;
    //return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
    gettimeofday(&tv, NULL);
    res = (size_t)tv.tv_usec;
    printf("\n%ld\n", tv.tv_sec);
    printf("\n%ld\n", tv.tv_sec * 1000);
    gettimeofday(&tv, NULL);
    printf("\n%ld\n",tv.tv_usec);
    printf("\n%ld\n",tv.tv_usec / 1000);
      
}