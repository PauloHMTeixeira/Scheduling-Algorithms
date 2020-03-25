#include "task.h"
#include "cpu.h"
#include "list.h"

#define SCHEDULER_NAME "FCFS"

#include "geral.h"

void schedule(void)
{
	prepare_operation();
	start_metrics();
	struct node *aux = procs;
	int wait_time = 0;
	while (aux != NULL) {
		Task *t = aux->task;
		run(t, t->burst);
		append_metrics(t->name,
				t->burst + wait_time,
				wait_time,
				wait_time);
		wait_time += t->burst;
		aux = aux->next;
	}
	print_metrics();
}
