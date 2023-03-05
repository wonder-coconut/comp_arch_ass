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

branch_node* search(branch_node *start, int addr)
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
    int i, j, addr, taken, predicted_taken;
    i = j = addr = taken = predicted_taken = 0;
    branch_node *start = (branch_node *) malloc (sizeof(branch_node));
    branch_node *current = (branch_node *) malloc (sizeof(branch_node));
    branch_node *temp = (branch_node *) malloc (sizeof(branch_node));

    while (fgetc(file) != EOF)
    {
        fscanf(file,"%x %d",&addr, &taken);
        if(i == 0)
        {
            start = createlist(addr, taken);
            current = start;
        }
        else
        {
            temp = search(start,addr);
            if (temp == NULL)
            {
                current = push(current, addr, taken);

                //printf("new entry: %x\t%d\n", current->addr, current->taken);
            }
            else
            {
                //printf("%d duplicate, updating\n", i);
                temp->taken = taken;
            }
        }
        i++;
    }
    current = start;
    i=0;
    fclose(file);
    while (current != NULL)
    {
        //printf("%d. %x\t%d\n",i++,current->addr,current->taken);
        current = current->next;
    }
    
}