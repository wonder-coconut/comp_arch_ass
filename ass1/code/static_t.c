#include <stdio.h>

int main()
{
    FILE *file;
    file = fopen("../traces/trace_01","r");
    char buff[13];
    char ch;
    int i = 0;
    int taken = 0;
    while (fgetc(file) != EOF)
    {
        fgets(buff,13,file);
        if(buff[8] == 49)//buff[8] = taken/not taken of branch address
            taken++;
        i++;
    }
    fclose(file);
    printf("Success:\t%d\n",taken);
    printf("Total:\t\t%d\n",i);
    printf("Accuracy:\t%f\n",(taken*1.0/i));
}