#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int i;

    for(i=0;;i++) {
        printf("%100\r", i);
        fflush(NULL);
        sleep(1);
    }
    return 0;
}

