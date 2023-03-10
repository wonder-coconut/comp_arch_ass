#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct branch_node
{
    unsigned int lsb_addr;
    int taken_state;
}branch_node;

int search(unsigned int lsb_addr, branch_node *arr, int arr_size)
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

    unsigned int addr, temp;
    int taken, n, i, j, top_index, total_correct_pred, default_state, prediction;
    addr = temp = taken = i = j = top_index = total_correct_pred = 0;
    default_state = 1;
    n = 30;
    int arr_size = (int)pow(2,n);
    branch_node *arr = (branch_node *) malloc(sizeof(branch_node) * arr_size);

    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        unsigned int lsb_addr = (addr<<(32-n))>>(32-n); //least significant n bits
        //printf("%x - ",lsb_addr);
        i = search(lsb_addr, arr, top_index);
        if (i == -1)
        {
            //printf("new addition : %x at %d\n",lsb_addr,top_index);
            arr[top_index].lsb_addr = lsb_addr;
            arr[top_index++].taken_state = taken+1;
            prediction = default_state;//prediction
        }
        else
        {
            //prediction
            if(arr[i].taken_state > 1)
                prediction = 1;
            else
                prediction = 0;
            //updation
            if(taken == 1)
                arr[i].taken_state = (++arr[i].taken_state > 3)?3:arr[i].taken_state;
            else
                arr[i].taken_state = (--arr[i].taken_state < 0)?0:arr[i].taken_state;
            //printf("duplicate found at %x\n",lsb_addr);
        }
        //printf("%d|\t %x %d %d %d\n",j++,lsb_addr,prediction,taken,total_correct_pred);
        if(prediction == taken)
            total_correct_pred++;
        j++;
    }

    fclose(file);

    printf("Success:\t%d\n",total_correct_pred);
    printf("Total:\t\t%d\n",j);
    printf("Accuracy:\t%f\n",(total_correct_pred*1.0/j));
}