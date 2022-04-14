#include "philo.h"

int main ()
{
    struct timeval tv;
    long res;

    gettimeofday(&tv, NULL);
    res = (size_t)tv.tv_sec;
    printf("%ld\n", res);
    sleep(10);
    gettimeofday(&tv, NULL);
    printf("%ld",tv.tv_sec - res);
}