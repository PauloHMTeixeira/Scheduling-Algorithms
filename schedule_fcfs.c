#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define QUANTUM 10

void schedule(char* name[],int array[],int array2[],int tamanho);

int main(int argc, char *argv[]){
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    
    char *array_nomes[SIZE];
    
    int array_priority[SIZE];
    int array_burst[SIZE];
    
    int priority;
    int burst;
    in = fopen(argv[1],"r");
    
    int i = 0;
    int j = 0;

    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        array_nomes[j] = name;
        j++;
        priority = atoi(strsep(&temp,","));
        array_priority[i] = priority;
        burst = atoi(strsep(&temp,","));
        array_burst[i] = burst;
        i++;
        free(temp);
    }

    fclose(in);
    printf("%d",i);
    schedule(array_nomes,array_priority,array_burst,i);
}

void schedule(char* name[],int array_priority[],int array_burst[],int tamanho){
    
    FILE *fp = fopen("fcfs.txt","a");

    fprintf(fp,"%s\n\n","EXECUTION BY FCFS");

    int turnaround = 0;
    int waiting = 0;
    int response = 0;
    double turnaround_total = 0;
    double waiting_total = 0;
    double response_total = 0;

    for(int i=0;i<tamanho;i++){
        fprintf(fp,"[%s] %s %d %s\n",name[i],"for",array_burst[i],"units");
    }
    fprintf(fp,"\n%s\n","METRICS");

    double media_turnaround = 0.0;
    double media_waiting = 0.0;
    double media_response = 0.0;

    for(int i=0; i<tamanho;i++){
        turnaround += array_burst[i];
        turnaround_total += turnaround;
        fprintf(fp,"\n[%s]\n",name[i]);
        fprintf(fp,"%s %s %d\n","Turnaround","time:",turnaround);
        fprintf(fp,"%s %s %d\n","Wainting","time:",waiting);
        fprintf(fp,"%s %s %d\n","Response","time:",response);
        if(i!=tamanho-1){
            waiting = turnaround;
            waiting_total += waiting;
            response = turnaround;
            response_total += response;
        }
    }
    
    media_turnaround = turnaround_total/(tamanho);
    media_waiting = waiting_total/(tamanho);
    media_response = response_total/(tamanho);

    fprintf(fp,"\n%s %s %s %s %f\n","Average","turnaround","time","=",media_turnaround);
    fprintf(fp,"%s %s %s %s %f\n","Average","waiting","time","=",media_waiting);
    fprintf(fp,"%s %s %s %s %f","Average","response","time","=",media_response);
}
