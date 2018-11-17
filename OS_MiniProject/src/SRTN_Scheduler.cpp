#include "SRTN_Scheduler.h"

SRTN_Scheduler::SRTN_Scheduler(Process* arr, unsigned long Size, Statistics& Stat)
{
    vector<Interval> allIntervals;      /// this vector contains all the processed intervals after finishing all the processes.
                                        /// this vector will be graphed after scheduling.

    for(int i=0; i<Size; i++)
        readyQueue.push_back(arr[i]);

    time = 0;

    double Min;
    int minIndex;
    while(!(readyQueue.empty() && running.empty()))     /// to finish all the scheduling, both ready and running processes must be empty.
    {
        if(!readyQueue.empty() && readyQueue[0].getArrivalTime() <= time)       /// if the first ready process time arrived.
        {
            /// move it from ready to running.
            running.push_back(readyQueue[0]);
            readyQueue.erase(readyQueue.begin());
        }

        if(!running.empty())        /// if there're some running processes.
        {
            Min = running[0].getRemainingTime();
            minIndex = 0;
            for(int i=1; i<running.size(); i++)     /// get the minimum remaining time of the running processes (to run it next).
            {
                if(running[i].getRemainingTime() < Min)
                {
                    Min = running[i].getRemainingTime();
                    minIndex = i;
                }
            }
            running[minIndex].setRemainingTime(Min-TIMESTAMP);      /// now it runs for TIMESTAMP amount of time.

            if(allIntervals.back().processID != running[minIndex].getProcessID())
            {
                Interval I(time,time+TIMESTAMP,running[minIndex].getProcessID());
                allIntervals.push_back(I);
            }
            else
                allIntervals.back().r += TIMESTAMP;

            if(running[minIndex].getRemainingTime() <= 0)      /// if the process finished
            {
                 /// we need to calculate and store its : waiting time, turnaround time, weighted turnaround time.
                processInfo PI;
                PI.ID = running[minIndex].getProcessID();
                PI.TAT = time - running[minIndex].getArrivalTime();
                PI.waitingTime = PI.TAT - running[minIndex].getBurstTime();
                PI.wieghtedTAT = PI.TAT / running[minIndex].getBurstTime();

                finishedVector.push_back(PI);

                running.erase(running.begin() + minIndex);
            }
        }
        time += TIMESTAMP;
    }

    Stat.setProcInfoVector(finishedVector);
    Stat.setGraphIntervals(allIntervals);
}

