#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <iostream>
#include <queue>
#include <algorithm>
#include "Process.h"

using namespace std;



class FCFS_Scheduler
{
    public:
        FCFS_Scheduler(Process* arr, unsigned long Size);

    private:
        struct processInfo
        {
            unsigned int ID,waitingTime,TAT,wieghtedTAT;
        };
        queue<Process> readyQueue;      /// this queue has all the processes in the ready state sorted in descending order waiting for their turn
        unsigned long clk;
        processInfo* finishedArr;
        int finishedArr_index;
};




#endif // FCFS_SCHEDULER_H
