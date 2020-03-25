#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"

struct node *head;

void add(char *name, int priority, int burst){
    Task* new = malloc(sizeof(Task));
    new->name = name;
    new->burst = burst;
    new->priority = priority;
    insert(&head,new);
}


void schedule(void){
    printf("EXECUTION BY FCFS");
    int wait = 0;
    int flag=0;
    while(head != NULL){
        Task *trash = head->task;
        run(trash,trash->burst);
        if(flag == 0){
            printf("\n METRICS \n");
            flag = 1;
        }
        printf("\n[%s]\n Turnaround time: %d\n Waiting time: %d\n Response time: %d\n",trash->name,trash->burst+wait,wait,wait);
        wait+=trash->burst;
        head = head->next;
    }
}
