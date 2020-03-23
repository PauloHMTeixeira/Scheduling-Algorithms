# Scheduling-Algorithms
Scheduling algorithms.
Completing this project will require writing the following C files:

schedule_fcfs.c
schedule_sjf.c
schedule_rr.c
schedule_priority.c
schedule_priority_rr.c
schedule_rm.c
schedule_edf.c

The supporting files invoke the appropriate scheduling algorithm. 

For example, to build the FCFS scheduler, enter

make fcfs

which builds the fcfs executable file.

Além dos algoritmos mencionados, dois outros devem ser implementados para simular sistemas de tempo real:

- rate-monotonic (rm)
- earliest-deadline-first (edf)

Nesses casos o arquivo de entrada terá a seguinte formatação:
[TOTAL TIME]
[TASK NAME] [CPU BURST] [PERIOD]

Para qualquer um dos algoritmos, a saída deverá ser o nome do mesmo com extensão txt (fcfs.txt, sjf.txt, priority.txt, rr.txt, priority_rr.txt, rm.txt ou edf.txt)

Uma melhor explicação dos arquivos de saída será exposta em sala de aula.
