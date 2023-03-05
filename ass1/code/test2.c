#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* substring(char* s, int init, int final)
{
    char *subs = (char*) malloc(sizeof(char)*(final-init));
    int j = 0;
    for (int i = init; i < final; i++)
        subs[j++] = s[i];
    return subs;
}

int main()
{
    char s[] = "10423094832";
    printf("%s\n", substring(s, 1, 5));
}