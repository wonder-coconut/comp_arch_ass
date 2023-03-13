#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dynamic_gshare(char filepath[], int n, int h)
{
    if(n == 0 || n > 31 || h > n)
    {
        printf("invalid n value\n");
        return 0;
    }
    FILE *file;
    file = fopen(filepath,"r");

    unsigned int addr, lsb_addr, history, index;
    int taken, i, total_correct_pred, default_state, prediction;
    addr = lsb_addr = history = index = taken = i = total_correct_pred = prediction = 0;
    default_state = 1;

    unsigned int arr_size = (int)pow(2,n);//2^n unique counters
    int *arr = (int *) malloc(arr_size * sizeof(int));
    
    for (i = 0; i < arr_size; i++)
        arr[i] = default_state;
    i = 0;

    clock_t t;
    t = clock();

    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        lsb_addr = (addr<<(32-n))>>(32-n); //least significant n bits //using 32 as int is 32bits
        index = lsb_addr ^ history; //xor
        
        //prediction
        if(arr[index] > 1) //2-3 (taken)
            prediction = 1;
        else //0-1 (taken)
            prediction = 0;
        
        if(prediction == taken)
            total_correct_pred++;

        //updation
        if(taken == 1)
            arr[index] = (++arr[index] > 3)? 3 : arr[index]; //saturated increment
        else
            arr[index] = (--arr[index] < 0)? 0 : arr[index]; //unsaturated increment

        history = (((history << 1) + taken)<< (32-h)) >> (32-h); //shift to add taken, then truncate to h bits
        if(h == 0)//range of shift is limited to 0-31 for uint
            history = 0;
   

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