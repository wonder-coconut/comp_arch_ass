#include <stdio.h>
#include <time.h>

int static_t(char filepath[])
{
    FILE *file;
    file = fopen(filepath,"r");
    char buff[13];
    char ch;
    int i = 0;
    int taken = 0;
    clock_t t;
    t = clock();
    while (fgetc(file) != EOF)
    {
        fgets(buff,13,file);
        if(buff[8] == 49)//buff[8] = taken/not taken of branch address
            taken++;
        i++;
    }
    t = clock() - t;
    fclose(file);

    printf("Success:\t%d\n",taken);
    printf("Total:\t\t%d\n",i);
    printf("Accuracy:\t%f\n",(taken*1.0/i));
    printf("Clock ticks:\t%ld\n",t);
    printf("Time:\t\t%f\n",((double)t/CLOCKS_PER_SEC));
}