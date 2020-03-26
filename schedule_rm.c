#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

void schedule(char *name[], int array[], int array2[], int tamanho);

int main(int argc, char *argv[])
{
  FILE *in;
  char *temp;
  char task[SIZE];

  char *name;

  char *array_nomes[SIZE];

  int array_deadline[SIZE];
  int array_burst[SIZE];

  char *total;
  int deadline;
  int burst;
  int aux0, aux2;
  char *aux1;

  in = fopen(argv[1], "r");

  int i = 0;
  int j = 0;
  int totaltime = 0;
  while (fgets(task, SIZE, in) != NULL)
  {
    temp = strdup(task);
    name = strsep(&temp, ",");
    array_nomes[j] = name;
    j++;
    deadline = atoi(strsep(&temp, ","));
    array_deadline[i] = deadline;
    burst = atoi(strsep(&temp, ","));
    array_burst[i] = burst;
    i++;
    free(temp);
  }

  fclose(in);
  printf("%d", i);
  for (int x = 0; x < i; x++)
  {
    for (int y = x + 1; y < i; y++)
    {
      if (array_burst[x] > array_burst[y])
      {
        if (total == 0)
        {
        }
        aux0 = array_burst[x];
        array_burst[x] = array_burst[y];
        array_burst[y] = aux0;
        aux1 = array_nomes[x];
        array_nomes[x] = array_nomes[y];
        array_nomes[y] = aux1;
        aux2 = array_deadline[x];
        array_deadline[x] = array_deadline[y];
        array_deadline[y] = aux2;
      }
    }
  }
  schedule(array_nomes, array_deadline, array_burst, i);
}

void schedule(char *name[], int array_deadline[], int array_burst[], int tamanho)
{

  FILE *fp = fopen("rma1.txt", "a");

  fprintf(fp, "%s\n\n", "EXECUTION BY RM");

  int i;
  int turnaround = 0;
  int waiting = 0;
  int response = 0;
  double turnaround_total = 0;
  double waiting_total = 0;
  double response_total = 0;

  int sumofburst = 0;
  int totaltime = array_deadline[0];

  for (int sum = 1; sum < tamanho; sum++)
  {
    sumofburst += array_burst[sum];
  }

  int tasktime = 0;      // utilizado para contar tempo geral de atividade
  int tasktimeA = 0;     // utilizado para contar tempo de atividade de A
  int tasktimeB = 0;     // utilizado para contar tempo de atividade de B
  int auxtime = 0;       // utilizado como um auxiliar para guardar valores específicos
  int killedA = 0;       // se matou A vai ficar > 0
  int killedB = 0;       // se matou B vai ficar > 0
  int completedA = 0;    // quantidade de vezes que completou A
  int completedB = 0;    // quantidade de vezes que completou B
  int lostDeadLineA = 0; // quantidade ed vezes que perdeu a Deadline de A
  int lostDeadLineB = 0; // quantidade ed vezes que perdeu a Deadline de B
  int idletime = 0;      // tempo ocioso
  int flag = 0;          // flag para se completar os 2, A e B

  printf("%d", array_deadline[1]);
  printf(" %d", array_deadline[2]);
  printf(" %d", array_burst[1]);
  printf(" %d", array_burst[2]);

  int time;
  while (1)
  {
    for (time = 0; time < 165; time++) // simulação de um clock iniciado com 2 tarefas síncronas utilizando rate monotonic scheduler
    {
      //se atingir 25 no tasktime e o tempo não é igual a própria DeadLine para não haver conflito com B
      if (tasktime == array_burst[1] && time != (completedA + lostDeadLineA) * array_deadline[1])
      {
        fprintf(fp, "\n[%s] %s %d %s", name[1], "for", array_burst[1], "units - F");
        tasktime = 0;
        completedA += 1;
      }
      //se atingir 25 no tasktime e o tempo não é igual a própria DeadLine para não haver conflito com A
      if (tasktime == array_burst[2] && time != (completedB + lostDeadLineB) * array_deadline[2])
      {
        fprintf(fp, "\n[%s] %s %d %s", name[2], "for", array_burst[2], "units - F");
        tasktime = 0;
        completedB += 1;
        flag = 2;
      }
      //se o tempo atingir a DeadLine de B e não tiver conseguido completar a segunda tarefa.
      if (time == array_deadline[2] && completedB == 0)
      {
        lostDeadLineB += 1;
      }
      //se o tempo atingir a DeadLine de A e não tiver conseguido completar a primeira tarefa.
      if (time == array_deadline[1] && completedA == 0)
      {
        lostDeadLineA += 1;
      }
      //se o tasktime + tasktime de B = Burst de B (para pegar o restante que faltou para terminar B)
      //e não começou a ser contabilizado a partir de uma deadline de A
      if ((tasktime + tasktimeB) == array_burst[2] && array_deadline[1] * (completedA + lostDeadLineA) != time - tasktime)
      {
        fprintf(fp, "\n[%s] %s %d %s", name[2], "for", tasktime, "units - F");
        completedB += 1;
        flag = 2;
        tasktimeB = 0;
      }
      //visto que a prioridade é sempre a primeira tarefa, nunca vai ser necessário realizar tasktime + tasktimeA

      //se os 2 tiverem sido terminados vai checar se existe idletime
      if (flag == 2)
      {
        if (array_deadline[1] * (completedA + lostDeadLineA) < array_deadline[2] * (completedB + lostDeadLineB))
        {
          if ((array_deadline[1] * (completedA + lostDeadLineA)) - time != 0)
          {
            idletime = (array_deadline[1] * (completedA + lostDeadLineA)) - time;
            fprintf(fp, "\n%s %d %s ", "idle for", idletime, "units");
          }
          tasktime = 0;
          time = time + idletime;
          flag = 0;
          break;
        }
      }
      //se o tempo alcançar o deadline da primeira tarefa, não for igual a zero e não tiver terminado os 2
      if (time == array_deadline[1] * (completedA + lostDeadLineA) && time != 0 && flag == 0)
      {
        //se for a primeira vez que atinge a deadline sem terminar a segunda tarefa
        if (tasktimeB != array_burst[2] && lostDeadLineB == 0)
        {
          tasktimeB = array_deadline[1] - array_burst[1];
          fprintf(fp, "\n[%s] %s %d %s", name[2], "for", tasktimeB, "units - H");
          tasktime = 0;
        }
        //se for mais que a primeira vez que atinge a deadline sem terminar a segunda tarefa
        if (tasktimeB != array_burst[2] && lostDeadLineB > 0)
        {
          tasktimeB = (array_deadline[1] * completedA) - array_deadline[2];
          fprintf(fp, "\n[%s] %s %d %s", name[2], "for", tasktimeB, "units - H");
          tasktime = 0;
        }
        tasktime = 0;
      }
      //se o tempo tiver atingido a deadline da segunda tarefa e o tempo não é zero
      if (time == array_deadline[2] * (completedB + lostDeadLineB) && time != 0)
      {
        //se ele não tiver concluído o Burst time da segunda tarefa até a deadline ele da como perdida
        if (tasktimeB != array_burst[2])
        {
          tasktimeB = tasktimeB + (array_deadline[2] - (array_burst[1] * (completedA) + tasktimeB));
          auxtime = array_burst[2] - tasktimeB;
          fprintf(fp, "\n[%s] %s %d %s", name[2], "for", auxtime, "units - L");
          tasktime = 0;
          tasktimeB = 0;
        }
        tasktime = 0;
      }
      flag = 0;
      tasktime++;
    }
    //aplicação da flag, para tratar se os 2 tiverem terminado e fazer a checagem se chegou em alguma deadline
    if (time == array_deadline[1] * completedA + (lostDeadLineA) || time == array_deadline[2] * (completedB + lostDeadLineB))
    {
      //se está perto de acabar, faltando menos tempo do que o Burst time de alguma das tarefas e checa qual deadline esta mais proxima
      if ((totaltime - time) < array_burst[1] && time != (array_deadline[2] * (completedB + lostDeadLineB)) &&
          (array_deadline[1] * (completedA + lostDeadLineA)) < (array_deadline[2] * (completedB + lostDeadLineB)))
      {
        fprintf(fp, "\n[%s] %s %d %s", name[1], "for", (totaltime - time), "units - K");
        killedA += 1;
        killedB += 1;
      }
      //se a deadline mais proxima for da segunda tarefa
      else if ((totaltime - time) < array_burst[2] && time != (array_deadline[1] * (completedB + lostDeadLineB)) &&
               (array_deadline[1] * (completedA + lostDeadLineA)) < (array_deadline[2] * (completedB + lostDeadLineB)))
      {
        fprintf(fp, "\n[%s] %s %d %s", name[2], "for", (totaltime - time), "units - K");
        killedA += 1;
        killedB += 1;
      }
      fprintf(fp, "\n\nLOST DEADLINES");
      fprintf(fp, "\n[%s] %d", name[1], lostDeadLineA);
      fprintf(fp, "\n[%s] %d", name[2], lostDeadLineB);
      fprintf(fp, "\n\nCOMPLETE EXECUTION");
      fprintf(fp, "\n[%s] %d", name[1], completedA);
      fprintf(fp, "\n[%s] %d", name[2], completedB);
      fprintf(fp, "\n\nKILLED");
      fprintf(fp, "\n[%s] %d", name[1], killedA);
      fprintf(fp, "\n[%s] %d", name[2], killedB);

      break;
    }
  }
}
