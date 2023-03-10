#include <stdio.h>
#include <string.h>
#include "static_t.c"
#include "static_nt.c"
#include "dynamic_lt.c"
#include "dynamic_bm.c"

int main(int argc, char *argv[])
{
    if(atoi(argv[1]) == 0 && argc == 3)//static_t
        static_t(argv[2]);// 0 <trace filepath>
    else if(atoi(argv[1]) == 1 && argc == 3)//static_nt
        static_nt(argv[2]);// 1 <trace filepath>
    else if(atoi(argv[1]) == 2 && argc == 3)//dynamic_lt
        dynamic_lt(argv[2]);// 2 <trace filepath>
    else if(atoi(argv[1]) == 3 && argc == 4)//dynamic_bm
        dynamic_bm(argv[2],atoi(argv[3]));// 3 <trace filepath> <n bit limit>
    else
        printf("incorrect arguments");
}