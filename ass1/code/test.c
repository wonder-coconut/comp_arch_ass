#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE *file;
    file = fopen("../traces/trace_01","r");

    unsigned int addr,taken,lsb_addr;
    lsb_addr = addr = taken;
    int n = 20;
    int arr_size = (int)pow(2,n);
    int max_addr = 0;

    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        lsb_addr = (addr<<(32-n))>>(32-n);
        if(lsb_addr > max_addr)
            max_addr = lsb_addr;
    }
    printf("Max addr:\t%d\nArray size:\t%d",max_addr, arr_size);
}