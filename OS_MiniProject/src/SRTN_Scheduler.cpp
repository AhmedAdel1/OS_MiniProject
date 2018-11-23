#include "SRTN_Scheduler.h"

SRTN_Scheduler::SRTN_Scheduler(Process* arr, unsigned long Size, Statistics& Stat)
{
    vector<Interval> allIntervals;      /// this vector contains all the processed intervals after finishing all the processes.
                                        /// this vector will be graphed after scheduling.

    for(int i=0; i<Size; i++)
        readyQueue.push_back(arr[i]);

    time = 0;

    double tempRem;     /// to determine the smallest remaining time.

    while(!(readyQueue.empty() && running.empty()))     /// to finish all the scheduling, both ready and running processes must be empty.
    {
        if(!readyQueue.empty() && readyQueue[0].getArrivalTime() <= time)       /// if the first ready process time arrived.
        {
            /// move it from ready to running.
            Process temp = readyQueue[0];
            readyQueue.erase(readyQueue.begin());

            /// we put it in its right place (where its remaining time is smallest in the vector)

            tempRem = temp.getRemainingTime();
            if(running.empty() || (!running.empty() && running.back().getRemainingTime() < tempRem))
                running.push_back(temp);
            else
            {
                int i;
                for(i=0; i<running.size(); i++)     /// get the minimum remaining time of the running processes (to run it next).
                {
                        if(running[i].getRemainingTime() > tempRem)
                    {
                        running.insert(running.begin() + i,temp);
                        break;
                    }
                }
            }


        }

        if(!running.empty())        /// if there're some running processes.
        {
            running[0].setRemainingTime(running[0].getRemainingTime()-TIMESTAMP);      /// now it runs for TIMESTAMP amount of time.

            if(!allIntervals.empty())
            {
                if(allIntervals.back().processID != running[0].getProcessID())
                {
                    Interval ContextInterv1(time,time+CONTEXT_TIME,-1);
                    allIntervals.push_back(ContextInterv1);
                    time += CONTEXT_TIME;
                    Interval I(time,time+TIMESTAMP,running[0].getProcessID());
                    allIntervals.push_back(I);
                }
                else
                    allIntervals.back().r += TIMESTAMP;
            }
            else{
                Interval ContextInterv(time,time+CONTEXT_TIME,-1);
                allIntervals.push_back(ContextInterv);
                time += CONTEXT_TIME;

                Interval I(time,time+TIMESTAMP,running[0].getProcessID());
                allIntervals.push_back(I);
            }

            if(running[0].getRemainingTime() <= 0)      /// if the process finished
            {
                 /// we need to calculate and store its : waiting time, turnaround time, weighted turnaround time.
                processInfo PI;
                PI.ID = running[0].getProcessID();
                PI.TAT = time - running[0].getArrivalTime();
                PI.waitingTime = PI.TAT - running[0].getBurstTime();
                PI.wieghtedTAT = PI.TAT / running[0].getBurstTime();

                finishedVector.push_back(PI);

                running.erase(running.begin());

            }
        }
        time += TIMESTAMP;
    }

    Stat.setProcInfoVector(finishedVector);
    Stat.setGraphIntervals(allIntervals);
}

