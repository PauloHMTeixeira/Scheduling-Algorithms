#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// A function to implement bubble sort 
void bubbleSort(int arr[], int n) 
{ 
   int i, j; 
   for (i = 0; i < n-1; i++)       
  
       // Last i elements are already in place    
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

int main(int argc, char *argv[]){
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;
    int wait[SIZE];
    double av_wait = 0;
    int turn_around[SIZE];
    double av_turn_around = 0;

    int turn[SIZE];
    int burst_time[SIZE];

    int number = 0;

    in = fopen(argv[1],"r");
    
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));
        burst_time[number] = burst;
        number++;

        free(temp);
    }

    
    bubbleSort(burst_time, number);

    //Set Wait Time
    wait[0]=0;
    for(int i=1;i<number;i++){
        wait[i]=0;
        for(int j=0;j<i;j++){
            wait[i]+=burst_time[j];
        }
    }

    //Set Turnaround Time, Average Turn Around and Average Wait
    for(int i=0;i<number;i++){
        turn_around[i] = burst_time[i] + wait[i];
        av_turn_around += turn_around[i];
        av_wait += wait[i];
    }
    av_wait = av_wait/number;
    av_turn_around = av_turn_around/number;

    fclose(in);

    //Write in the file
    FILE *out = fopen("sjf_teste.tx", "w");
    fprintf(out,"EXECUTION BY SJF\n\n");
    char *msg;
    for (int i = 0; i < number; i++){
        // msg = "[T%d] for %d\n",i ,burst_time[i];
        fprintf(out,"[T%d] for %d units\n",i+1 ,burst_time[i]);
    }

    fprintf(out,"\nMETRICS\n");
    
    for (int i = 0; i < number; i++){
        // msg = "\n[T%d]\nTurnaround time: %d\nWaiting time: %d\nResponse time:%d", i, turn_around[i], wait[i], wait[i];
        fprintf(out,"\n[T%d]\nTurnaround time: %d\nWaiting time: %d\nResponse time:%d\n", i+1, turn_around[i], wait[i], wait[i]);
    }

    // msg = "\nAverage turnaround time = %d\nAverage waiting time = %d\nAverage response time = %d",av_turn_around, av_wait, av_wait;
    fprintf(out,"\nAverage turnaround time = %f\nAverage waiting time = %f\nAverage response time = %f",av_turn_around, av_wait, av_wait);
    fclose(out);
 
    return 0;
}