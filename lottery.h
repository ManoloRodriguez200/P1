#include <setjmp.h>

#ifndef LOTTERY_H_
#define LOTTERY_H_

// Definition of structs used in the software
struct Thread
{
    int quantum;
    int tickets;
    int completed;
    int percentageCompleted;
    sigjmp_buf buffer;
};

typedef struct Thread Thread;

//Pre-definition of methods implemented in the software
int selectWinnerThread(Thread* threads);
int getTotalTickets(Thread* threads);
void scheduler(Thread* threads);
void temp(Thread threads);
Thread doCalculations(Thread thread);
int evaluateAccomplish(Thread* threads);

#endif
