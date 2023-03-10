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
    file = fopen("../traces/trace_01_test","r");

    int i, j, addr, taken, prediction, total_correct_pred, default_state;
    i = j = addr = taken = prediction = total_correct_pred = 0;
    default_state = 1;
    
    branch_node *start = (branch_node *) malloc (sizeof(branch_node));
    branch_node *current = (branch_node *) malloc (sizeof(branch_node));
    branch_node *temp = (branch_node *) malloc (sizeof(branch_node));

    while (fscanf(file,"%x %d",&addr, &taken) != EOF)
    {
        if(i == 0)//initial node
        {
            prediction = default_state;//default state for new trace address
            start = createlist(addr, taken);
            current = start;
        }
        else
        {
            temp = search(start,addr);
            if (temp == NULL)
            {
                prediction = default_state;//default state for new trace address
                current = push(current, addr, taken);
            }
            else //trace node found in list
            {
                /*prediction is taken as the <taken> state of the node found in the list
                i.e. the previous taken state of the trace address*/
                prediction = temp->taken;
                temp->taken = taken; //trace node <taken> state is updated to current 
            }
        }
        if(prediction == taken)
            total_correct_pred++;
        //printf("%d : %d - %d - %d - %x\n",i, prediction,taken, total_correct_pred, addr);
        i++;
    }

    current = start;
    j = 0;
    fclose(file);
    while (current != NULL)
    {
        printf("%d|\t%x\n",j++,current->addr);
        current = current->next;
    }
    
    printf("Success:\t%d\n",total_correct_pred);
    printf("Total:\t\t%d\n",i);
    printf("Accuracy:\t%f\n",(total_correct_pred*1.0/i));
}