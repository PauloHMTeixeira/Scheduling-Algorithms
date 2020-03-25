#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

struct node *head;
struct node *units;
struct node *aux0;
struct node *aux1;
struct node *swap;

void add(char *name, int priority, int burst){
    Task* new = malloc(sizeof(Task));
    new->name = name;
    new->burst = burst;
    new->priority = priority;
    insert(&head,new);
    insert(&units,new);
}

void schedule(void){
    Task *sort = malloc(sizeof(Task));
    FILE *fp = fopen("priority.txt","a");
    fprintf(fp,"EXECUTION BY PRIORITY\n");
    int wait=0;
    int flag=0;
    int total=9999;      
    int count=0;

    while(units != NULL){
        //printf("oi");
        //Task *printa = units->task;
        units = units->next;
        count++;
    }

    int j=0;
    for(int i = 0;i<total;i++){
        for(j = 0;j<count;j++){
            if(head->task->priority == i){
                insert(&head,sort);
            }
        }
        if(j==count){
            break;
        }
        head = head->next;
    }
    

    while(units != NULL){
        //printf("oi");
        run(sort,sort->burst,fp);
        units = units->next;
    }

    fprintf(fp,"\n");

    while(head != NULL){
        if(flag == 0){
            fprintf(fp,"\nMETRICS\n\n");
            flag = 1;
        }
        fprintf(fp,"\n[%s]\nTurnaround time: %d\nWaiting time: %d\nResponse time: %d\n",sort->name,sort->burst+wait,wait,wait);
        wait+=sort->burst;
        head = head->next;
    }
}