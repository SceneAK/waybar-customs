#include <stdio.h>
#include <unistd.h>

int main()
{
    int count = 0;
    while(1)
    {
        count++;
        sleep(1);
        printf("TEST: %d \n", count);
        fflush(stdout);
    }
}
