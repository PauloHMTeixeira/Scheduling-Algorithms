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
    int aux0, aux2;
    char* aux1;
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
    for(int x = 0; x < i; x++ )
        {
        for(int y = x + 1; y < i; y++ )
        {
        if ( array_priority[x] < array_priority[y] )
        {
            aux0 = array_priority[x];
            array_priority[x] = array_priority[y];
            array_priority[y] = aux0;
            aux1 = array_nomes[x];
            array_nomes[x] = array_nomes[y];
            array_nomes[y] = aux1;
            aux2 = array_burst[x];
            array_burst[x] = array_burst[y];
            array_burst[y] = aux2;
            }
        }
    }
    schedule(array_nomes,array_priority,array_burst,i);
}

void schedule(char* name[],int array_priority[],int array_burst[],int tamanho){

    FILE *fp = fopen("priority_rr.txt","a");

    fprintf(fp,"%s\n\n","EXECUTION BY PRIORITY RR");

    int aux_burst[tamanho];
    int aux_response[tamanho];

    for(int i=0;i<tamanho;i++){
        aux_burst[i] = array_burst[i];
        aux_response[i] = QUANTUM*i;
    }

    int turnaround = 0;
    int waiting = 0;
    int response = 0;
    double turnaround_total = 0;
    double waiting_total = 0;
    double response_total = 0;

    double media_turnaround = 0.0;
    double media_waiting = 0.0;
    double media_response = 0.0;

    int restante = 0;
    int tempo=0;
    int marcador;
    int i=0;

    while(1){
        if(restante==tamanho){
            break;
        }
        else{
            if(aux_burst[i]>0 && aux_burst[i]>=QUANTUM){
                fprintf(fp,"[%s] %s %d %s\n",name[i],"for",QUANTUM,"units");
            }if(aux_burst[i]>0 && aux_burst[i]<QUANTUM){
                fprintf(fp,"[%s] %s %d %s\n",name[i],"for",aux_burst[i],"units");
            }
            if(aux_burst[i]<=QUANTUM && aux_burst[i]>0){
                aux_burst[i]=0;
                marcador=1;
            }else if(aux_burst[i]>0){
                aux_burst[i]-=QUANTUM;
            }if(aux_burst[i]==0 && marcador==1){
                restante++;
                marcador=0;
            }
            i++;
            if(tamanho==i){
                i=0;
            }
        }
    }

    for(int i=0;i<tamanho;i++){
        aux_burst[i] = array_burst[i];
    }
    
    restante = 0;
    i = 0;

    fprintf(fp,"\n%s\n","METRICS");

    while(1){
        if(restante==tamanho){
            break;
        }
        else{
           // printf("nome: %s ----------- tempo restante: %d\n",name[i],aux_burst[i]);
            if(aux_burst[i]<=QUANTUM && aux_burst[i]>0){
                tempo += aux_burst[i];
                aux_burst[i]=0;
                marcador=1;
            }else if(aux_burst[i]>0){
                aux_burst[i]-=QUANTUM;
                tempo += QUANTUM;
            }if(aux_burst[i]==0 && marcador==1){
                turnaround_total += tempo;
                waiting=tempo-array_burst[i];
                response+=tempo-array_burst[i];
                fprintf(fp,"\n[%s]\n",name[i]);
                fprintf(fp,"%s %s %d\n","Turnaround","time:",tempo);
                fprintf(fp,"%s %s %d\n","Wainting","time:",waiting);
                fprintf(fp,"%s %s %d\n","Response","time:",aux_response[i]);
                waiting_total+=waiting;
                response_total+=aux_response[i];
                marcador = 0;
                restante++;
            }
            i++;
            if(tamanho==i){
                i=0;
            }
        }
        
    }
    
    media_turnaround = turnaround_total/tamanho;
    media_waiting = waiting_total/tamanho;
    media_response = response_total/tamanho;


    fprintf(fp,"\n%s %s %s %s %f\n","Average","turnaround","time","=",media_turnaround);
    fprintf(fp,"%s %s %s %s %f\n","Average","waiting","time","=",media_waiting);
    fprintf(fp,"%s %s %s %s %f","Average","response","time","=",media_response);
}
