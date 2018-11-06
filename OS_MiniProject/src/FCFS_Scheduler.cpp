#include "FCFS_Scheduler.h"

FCFS_Scheduler::FCFS_Scheduler(Process* arr, unsigned long Size)
{
    /// 1) first step, we need to push the array into the ready queue.

    for(unsigned long i =0; i<Size; i++)
        readyQueue.push(arr[i]);

    /**
    cout << "printing the queue" << endl;

    while(!readyQueue.empty())
    {
        cout << readyQueue.front().getProcessID() << "\t" << readyQueue.front().getArrivalTime() << "\t" << readyQueue.front().getBurstTime() << "\t" << readyQueue.front().getPriority() << "\t" << endl;
        readyQueue.pop();
    }
    **/

    clk = 0;
    finishedArr_index = 0;
    finishedArr = new processInfo[Size];

    while(!readyQueue.empty())
    {
        Process temp = readyQueue.front();
        while(temp.getArrivalTime() > clk)
            clk++;

        /// if reached here, then the first element in the queue starts now.
        /// in this algorithm, we run the entire process until it's done.

        clk += temp.getBurstTime();

        /// we need to calculate and store its : waiting time, turnaround time, weighted turnaround time.

        finishedArr[finishedArr_index].ID = temp.getProcessID();
        finishedArr[finishedArr_index].TAT = clk - temp.getArrivalTime();
        finishedArr[finishedArr_index].waitingTime = finishedArr[finishedArr_index].TAT - temp.getBurstTime();
        finishedArr[finishedArr_index].wieghtedTAT = finishedArr[finishedArr_index].TAT / temp.getBurstTime();

        readyQueue.pop();
        finishedArr_index++;
    }

    cout << "printing statistics \n";
    for(int i = 0; i < Size; i++)
    {
        cout << finishedArr[i].ID << "\t" << finishedArr[i].TAT << "\t" << finishedArr[i].waitingTime << "\t" << finishedArr[i].wieghtedTAT << endl;
    }
}

