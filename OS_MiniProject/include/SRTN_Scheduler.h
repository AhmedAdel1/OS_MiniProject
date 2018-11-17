#ifndef SRTN_SCHEDULER_H
#define SRTN_SCHEDULER_H

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include "Process.h"
#include "processInfo.h"
#include "Statistics.h"
#include "Interval.h"

using namespace std;

class SRTN_Scheduler
{
    public:
        SRTN_Scheduler(Process* arr, unsigned long Size, Statistics& Stat);

    private:
        vector<Process> readyQueue;      /// this vector has all the processes in the ready state sorted in descending order waiting for their turn
        vector<Process> running;               /// vector of the running processes.

        double time;
        vector<processInfo> finishedVector;
};

#endif // SRTN_SCHEDULER_H
