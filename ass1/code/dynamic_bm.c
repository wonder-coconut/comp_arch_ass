#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dynamic_bm(char filepath[], int n)
{
    if(n == 0 || n >= 30)
    {
        printf("invalid n value\n");
        return 0;
    }
    FILE *file;
    file = fopen(filepath,"r");

    unsigned int addr, lsb_addr;
    int taken, i, total_correct_pred, default_state, prediction;
    addr = lsb_addr = taken = i = total_correct_pred = prediction = 0;
    default_state = 1;
    int arr_size = (int)pow(2,n);//2^n unique counters
    int *arr = (int *) malloc(arr_size * sizeof(int));
    for (i = 0; i < arr_size; i++)
        arr[i] = default_state;
    
    i = 0;

    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        lsb_addr = (addr<<(32-n))>>(32-n); //least significant n bits //using 32 as int is 32bits

        //prediction
        if(arr[lsb_addr] > 1) //2-3 (taken)
            prediction = 1;
        else //0-1 (taken)
            prediction = 0;
        
        if(prediction == taken)
            total_correct_pred++;

        //updation
        if(taken == 1)
            arr[lsb_addr] = (++arr[lsb_addr] > 3)? 3 : arr[lsb_addr]; //saturated increment
        else
            arr[lsb_addr] = (--arr[lsb_addr] < 0)? 0 : arr[lsb_addr]; //unsaturated increment

        i++;
    }

    fclose(file);

    printf("Success:\t%d\n",total_correct_pred);
    printf("Total:\t\t%d\n",i);
    printf("Accuracy:\t%f\n",(total_correct_pred*1.0/i));
}