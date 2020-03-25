/*
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>

#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice, FILE *file) {
    fprintf(file,"\n[%s] for %d units.",task->name,slice);
}
