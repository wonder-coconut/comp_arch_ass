#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct branch_node
{
    unsigned int lsb_addr;
    int taken_state; //0-1-2-3
}branch_node;

int search(unsigned int lsb_addr, branch_node *arr, int arr_size)//linear search
{
    for (int i = 0; i < arr_size; i++)
    {
        if(arr[i].lsb_addr == lsb_addr)
            return i;
    }
    return -1;
}

int main()
{
    FILE *file;
    file = fopen("../traces/trace_01","r");

    unsigned int addr, temp, lsb_addr;
    int taken, n, i, j, top_index, total_correct_pred, default_state, prediction;
    addr = temp = lsb_addr = taken = i = j = top_index = total_correct_pred = 0;
    default_state = 1;
    n = 24;
    int arr_size = (int)pow(2,n);//2^n unique counters
    branch_node *arr = (branch_node *) malloc(sizeof(branch_node) * arr_size);

    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        lsb_addr = (addr<<(32-n))>>(32-n); //least significant n bits
        i = search(lsb_addr, arr, top_index);
        if (i == -1)
        {
            arr[top_index].lsb_addr = lsb_addr;
            arr[top_index++].taken_state = taken+1;//converting to 2 bit state 
            //(0 becomes 1 (weakly not taken) and 1 becomes 2(weakly taken))
            prediction = default_state;//prediction
        }
        else
        {
            //prediction
            if(arr[i].taken_state > 1) //2-3 taken
                prediction = 1;
            else //0-1 not taken
                prediction = 0;
            //updation
            if(taken == 1)
                arr[i].taken_state = (++arr[i].taken_state > 3)?3:arr[i].taken_state; //saturated increment
            else
                arr[i].taken_state = (--arr[i].taken_state < 0)?0:arr[i].taken_state; //saturated decrement
        }
        if(prediction == taken)
            total_correct_pred++;
        j++;
    }

    fclose(file);

    printf("Success:\t%d\n",total_correct_pred);
    printf("Total:\t\t%d\n",j);
    printf("Accuracy:\t%f\n",(total_correct_pred*1.0/j));
}