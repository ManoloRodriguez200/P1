#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "lottery.h"

///---------------------------------------------------------
///--- Global variables used for the read arguments ---

// Operational mode
int mode; // 1 for preemptive 0 for non preemptive

// Threads number
int threadsNumber;

// Quantum for threads in preemptive mode
int quantum = 0;

// Variable to know if the total work hass been accomplished
int workAccomplished = 0;

sigjmp_buf localBufferForTest;

///---------------------------------------------------------

int main(int argc, char* argv[])
{
    threadsNumber = atoi(argv[1]);
    mode = atoi(argv[threadsNumber + 2]);
    if(mode == 1) quantum = atoi(argv[threadsNumber + 3]);
    
    Thread threadsArray[threadsNumber];
    for(int i = 0; i < threadsNumber; i++)
    {
        threadsArray[i].quantum = quantum;
        threadsArray[i].tickets = atoi(argv[i+2]);
        threadsArray[i].completed = 0;
        threadsArray[i].percentageCompleted = 0;
    }
    
    scheduler(threadsArray);
    
}

int selectWinnerThread(Thread* threads)
{
    int totalTickets = getTotalTickets(threads);
    int selected;
    int r = rand()%(totalTickets + 1); 
    int sum = 0;
    
    for(int i = 0; i < threadsNumber; i++)
    {
        sum += threads[i].tickets;
        if(sum >= r) 
        {
            selected = i;
            break;
        }
    }
    
    //printf("Total tickets: %d, ticket selected: %d, winner thread: %d\n", totalTickets, r, selected);
    
    return selected;
}

int getTotalTickets(Thread* threads)
{
    int total = 0;
    
    for(int i = 0; i < threadsNumber; i++)
    {
        total += threads[i].tickets;
    }
    
    return total;
}

void scheduler(Thread* threads)
{
    srand(time(NULL));
    
    while(workAccomplished < 1) 
    {
        int winner = selectWinnerThread(threads);
        
        printf("------------------------------------------------\n");
        printf("Winner Thread: %d\n",winner+1);
        threads[winner] = doCalculations(threads[winner]);
        printf("------------------------------------------------\n");
        workAccomplished = evaluateAccomplish(threads);
    }
}

Thread doCalculations(Thread thread)
{
    
    if(mode == 0)
    {       
        int percentageCompletedForTransferCpu = 20;
        int currentPercentageAdvance = 0;
        
        while(thread.completed < 1 && currentPercentageAdvance < percentageCompletedForTransferCpu)
        {
            currentPercentageAdvance += 10; // AGREGAR LOS CALCULOS DE LO QUE MANOLO ESTA HACIENDO
        }
        
        thread.percentageCompleted += currentPercentageAdvance;
        
        if(thread.percentageCompleted >= 100) //arreglar para que la solucion sea == 100 y no >= 100
        {
            thread.completed++;
            thread.tickets = 0;
        }
    }
    else if(mode == 1)
    {   
        time_t startTime = time(NULL);
        time_t localQuantum = quantum;
        time_t endTime = startTime + localQuantum;
        
        //printf("Percentage Completed Initial: %d\n", thread.percentageCompleted);
        
        while(thread.completed < 1 && startTime < endTime)
        {
            startTime = time(NULL); // AGREGAR LOS CALCULOS DE LO QUE MANOLO ESTA HACIENDO
        }
        
        thread.percentageCompleted += 20;
       
        if(thread.percentageCompleted >= 100) //arreglar para que la solucion sea == 100 y no >= 100
        {
            thread.completed++;
            thread.tickets = 0;
        }
        printf("Work interrupted (quantum exceded)\n");
    } 
    //printf("Percentage Completed Final: %d\n", thread.percentageCompleted);
    printf("Percentage Completed: %d\n", thread.percentageCompleted);
    
    if(sigsetjmp(localBufferForTest, 1))
        {
            printf("AA\n");
            temp(thread);
            exit(0);
        }
        
    return thread;
}

void temp(Thread thread)
{
    printf("BB\n");
    siglongjmp(localBufferForTest, 1);   
}
    
int evaluateAccomplish(Thread* threads)
{
    int completedWork = 1;
    
    for(int i = 0; i < threadsNumber; i++)
    {
        if(threads[i].percentageCompleted < 100) 
        {
            completedWork = 0;
        }
        else
        {
            printf("Thread[%d] completed\n", i+1);
            printf("Thread[%d] tickets: %d\n", i+1, threads[i].tickets);
        }
    }
    
    return completedWork;
}
