#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printbin(unsigned int n)
{
    int arr[255];
    int i = 0;
    while (n != 0)
    {
        arr[i++] = n%2;
        n/=2;
    }
    while (i > 0)
        printf("%d",arr[--i]);
    printf("\n");
}
int main()
{
    /*int arr[] = {1,1,1,0,1,0,1,0,0,1,0,1,0,0,0,0,1};
    int arr_size = sizeof(arr)/sizeof(int);
    unsigned int history = 0;
    int h = 0;
    for (int i = 0; i < arr_size; i++)
    {
        history = (((history << 1) + arr[i]) << (32-h)) >> (32-h);
        printbin(history);
    }*/
    unsigned int n = 255;
    n = (n<<32)>>32;
    printf("%d\n",n);
}