#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head;
struct node *units;

void add(char *name, int priority, int burst){
    Task* new = malloc(sizeof(Task));
    new->name = name;
    new->burst = burst;
    new->priority = priority;
    insert(&head,new);
    insert(&units,new);
}


void schedule(void){
    FILE *fp = fopen("fcfs.txt","a");
    fprintf(fp,"EXECUTION BY FCFS\n");
    int wait = 0;
    int flag=0;

    while(units != NULL){
        //printf("oi");
        Task *printa = units->task;
        run(printa,printa->burst,fp);
        units = units->next;
    }

    fprintf(fp,"\n");

    while(head != NULL){
        if(flag == 0){
            fprintf(fp,"\nMETRICS\n\n");
            flag = 1;
        }
        Task *metric = head->task;
        fprintf(fp,"\n[%s]\nTurnaround time: %d\nWaiting time: %d\nResponse time: %d\n",metric->name,metric->burst+wait,wait,wait);
        wait+=metric->burst;
        head = head->next;
    }
}
