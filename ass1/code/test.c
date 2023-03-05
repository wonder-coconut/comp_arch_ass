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
    int arr[] = {1,2,3,4,5,9,8,7,6};
    int len = sizeof(arr)/sizeof(arr[0]);
    branch_node *start;
    branch_node *current;
    for (int i = 0; i < len; i++)
    {
        if(i == 0)
        {
            start = createlist(arr[i],0);
            current = start;
        }
        else
            current = push(current, arr[i], 0);
    }
    current = start;
    while (current != NULL)
    {
        printf("%d %d\n",current->addr, current->taken);
        current = current->next;
    }

    current = search(start,1);
    if(current == NULL)
        printf("not found\n");
    else
    {
        printf("found %d\n",current->addr);
    }
}