#include <stdio.h>
#include <stdlib.h>

typedef struct branch_node
{
    int addr;
    int taken;
    struct branch_node *next;
}branch_node;

branch_node* createlist(int addr, int taken) 
{
    branch_node *start = (branch_node*) malloc (sizeof(branch_node));
    start->addr = addr;
    start->taken = taken;
    start->next = NULL;
    return start;
}

branch_node* push(branch_node *current, int addr, int taken)
{
    branch_node *new_node = (branch_node*) malloc (sizeof(branch_node));
    current->next = new_node;
    new_node->addr = addr;
    new_node->taken = taken;
    new_node->next = NULL;
    return new_node;
}

branch_node* search(branch_node *start, int addr)// linear search to look for a matching address in a linked list
{
    branch_node *current = start;
    while (current != NULL)
    {
        if(current->addr == addr)
            return current;
        current = current->next;
    }
    return NULL;
}

int main()
{
    FILE *file;
    file = fopen("../traces/trace_01","r");

    int i, j, addr, taken, predicted_taken, total_taken;
    i = j = addr = taken = predicted_taken = total_taken = 0;
    
    branch_node *start = (branch_node *) malloc (sizeof(branch_node));
    branch_node *current = (branch_node *) malloc (sizeof(branch_node));
    branch_node *temp = (branch_node *) malloc (sizeof(branch_node));

    while (fgetc(file) != EOF)
    {
        fscanf(file,"%x %d",&addr, &taken);
        if(i == 0)//initial node
        {
            predicted_taken = 1;//default state for new trace address
            start = createlist(addr, taken);
            current = start;
        }
        else
        {
            temp = search(start,addr);
            if (temp == NULL)
            {
                predicted_taken = 1;//default state for new trace address
                current = push(current, addr, taken);
            }
            else //trace node found in list
            {
                /*prediction is taken as the <taken> state of the node found in the list
                i.e. the previous taken state of the trace address*/
                predicted_taken = temp->taken;
                temp->taken = taken; //trace node <taken> state is updated to current 
            }
        }
        if(predicted_taken == taken)
            total_taken++;
        //printf("%d : %d - %d - %d - %x\n",i, predicted_taken,taken, total_taken, addr);
        i++;
    }

    fclose(file);
    printf("Success:\t%d\n",total_taken);
    printf("Total:\t\t%d\n",i);
    printf("Accuracy:\t%f\n",(total_taken*1.0/i));
}