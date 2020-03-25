#ifndef GERAL_H
#define GERAL_H

#include <stdlib.h>
#include <stdio.h>

struct node *procs;
int proc_count = 0;

void add(char *name, int priority, int burst)
{
	Task *nt = malloc(sizeof(Task));
	nt->name = name;
	nt->tid = proc_count;
	nt->priority = priority;
	nt->burst = burst;
	insert(&procs, nt);
}

char metrics[10 * 1024]; /* 10kb output file */
char *metrics_current = metrics;

void start_metrics()
{
	metrics_current += sprintf(metrics, "METRICS\n");
}

void append_metrics(char *name, int ta_time, int w_time, int r_time)
{
	metrics_current += sprintf(
			metrics_current,
			"\n"
			"[%s]\n"
			"Turnaround time: %d\n"
			"Waiting time: %d\n"
			"Response time: %d\n",
			name, ta_time, w_time, r_time);
}

void print_metrics(void)
{
	printf("\n%s", metrics);
	return;
}

void prepare_operation(void)
{
	printf("EXECUTION BY %s\n\n", SCHEDULER_NAME);
}

#endif
