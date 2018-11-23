#ifndef FCFS_SCHEDULER_H
#define FCFS_SCHEDULER_H

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include "Process.h"
#include "Interval.h"
#include "Statistics.h"
#include "processInfo.h"

using namespace std;



class FCFS_Scheduler
{
    public:
        FCFS_Scheduler(Process* arr, unsigned long Size,double contextTime, Statistics& Stat);

    private:
        queue<Process> readyQueue;      /// this queue has all the processes in the ready state sorted in descending order waiting for their turn
        double time;
        vector<processInfo> finishedVector;
};




#endif // FCFS_SCHEDULER_H
