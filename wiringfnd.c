#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int fndControl(int num)
{
    int i;
    int gpiopins[4] = {4, 1, 16, 15};
    
    int number[10][4] = { {0,0,0,0},
                          {0,0,0,1},
                          {0,0,1,0},
                          {0,0,1,1},
                          {0,1,0,0},
                          {0,1,0,1},
                          {0,1,1,1},
                          {1,0,0,0},
                          {1,0,0,1} };

    for(i=0; i<4; i++) {
        pinMode(gpiopins[i], OUTPUT);
    }
    for(i=0; i<4; i++) {
        digitalWrite(gpiopins[i], number[num][i]?HIGH:LOW);
    }     
    getchar();

    for(int i=0; i<4; i++) {
        digitalWrite(gpiopins[i], HIGH);
    }
    return 0;
}

int main(int argc, char **argv)
{
    int no;

    if(argc < 2) {
        printf("Usage: %s NO\n", argv[0]);
        return -1;
    }
    no = atoi(argv[1]);
    wiringPiSetup();
    fndControl(no);

    return 0;
}


