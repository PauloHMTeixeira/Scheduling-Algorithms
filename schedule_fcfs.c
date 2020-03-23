#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void schedule(char* name[],int array[],int tamanho);

int main(int argc, char *argv[]){
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    
    char *array_nomes[SIZE];
    
    int array_inteiros[SIZE];
    
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
        array_inteiros[i] = priority;
        i++;
        burst = atoi(strsep(&temp,","));
        array_inteiros[i] = burst;
        i++;
        free(temp);
    }

    fclose(in);

    schedule(array_nomes,array_inteiros,i);
}

void schedule(char* name[],int array_inteiros[],int tamanho){
    
    FILE *fp = fopen("fcfs","a");

    fprintf(fp,"%s\n\n","EXECUTION BY FCFS");

    int turnaround = 0;
    int waiting = 0;
    int response = 0;

    for(int i=0;i<tamanho;i++){
        fprintf(fp,"[%s] %s %d %s\n",name[i/2],"for",array_inteiros[i+1],"units");
        i++;
    }
    fprintf(fp,"\n%s\n","METRICS");

    float media_turnaround = 0.0;
    float media_waiting = 0.0;
    float media_response = 0.0;

    for(int i=0; i<tamanho;i++){
        turnaround += array_inteiros[i+1];
        fprintf(fp,"\n[%s]\n",name[i/2]);
        fprintf(fp,"%s %s %d\n","Turnaround","time:",turnaround);
        fprintf(fp,"%s %s %d\n","Wainting","time:",waiting);
        fprintf(fp,"%s %s %d\n","Response","time:",response);
        if(i!=tamanho-2){
            waiting = turnaround;
            response = turnaround;
        }
        i++;
    }
    
    media_turnaround = turnaround/(tamanho/2);
    media_waiting = waiting/(tamanho/2);
    media_response = response/(tamanho/2);

    fprintf(fp,"\n%s %s %s %s %f\n","Average","turnaround","time","=",media_turnaround);
    fprintf(fp,"%s %s %s %s %f\n","Average","waiting","time","=",media_waiting);
    fprintf(fp,"%s %s %s %s %f","Average","response","time","=",media_response);
}