#include <stdio.h>
#include <string.h>
#include "static_t.c"
#include "static_nt.c"
#include "dynamic_lt.c"
#include "dynamic_bm.c"
#include "dynamic_gshare.c"

int main(int argc, char *argv[])
{
    if(atoi(argv[1]) == 1 && argc == 3)//static_t
        static_t(argv[2]);// 1 <trace filepath>
    else if(atoi(argv[1]) == 2 && argc == 3)//static_nt
        static_nt(argv[2]);// 2 <trace filepath>
    else if(atoi(argv[1]) == 3 && argc == 3)//dynamic_lt
        dynamic_lt(argv[2]);// 3 <trace filepath>
    else if(atoi(argv[1]) == 4 && argc == 4)//dynamic_bm
        dynamic_bm(argv[2], atoi(argv[3]));// 4 <trace filepath> <n bit limit>
    else if(atoi(argv[1]) == 5 && argc == 5)//dynamic_gshare
        dynamic_gshare(argv[2], atoi(argv[3]), atoi(argv[4]));//5 <trace filepath> <n bit limit> <h bit limit>
    else
        printf("incorrect arguments");
}