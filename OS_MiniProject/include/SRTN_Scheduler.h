#ifndef SRTN_SCHEDULER_H
#define SRTN_SCHEDULER_H

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include "Process.h"

using namespace std;

class SRTN_Scheduler
{
    public:
        SRTN_Scheduler(Process* arr, unsigned long Size);

    private:
        struct processInfo
        {
            unsigned int ID,waitingTime,TAT,wieghtedTAT;
        };

        vector<Process> readyQueue;      /// this vector has all the processes in the ready state sorted in descending order waiting for their turn
        vector<Process> running;               /// vector of the running processes.

        unsigned long clk;
        processInfo* finishedArr;
        int finishedArr_index;
};

#endif // SRTN_SCHEDULER_H
