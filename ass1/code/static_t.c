#include <stdio.h>
#include <time.h>

int static_t(char filepath[])
{
    FILE *file;
    file = fopen(filepath,"r");
    int i = 0;
    unsigned int addr;
    int prediction, taken, total_correct_pred;
    taken = total_correct_pred = 0;
    prediction = 1;
    clock_t t;
    t = clock();
    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        if(prediction == taken)
            total_correct_pred++;
        i++;
    }
    t = clock() - t;
    fclose(file);

    printf("Success:\t%d\n",total_correct_pred);
    printf("Total:\t\t%d\n",i);
    printf("Accuracy:\t%f\n",(total_correct_pred*1.0/i));
    printf("Clock ticks:\t%ld\n",t);
    printf("Time:\t\t%f\n",((double)t/CLOCKS_PER_SEC));
}