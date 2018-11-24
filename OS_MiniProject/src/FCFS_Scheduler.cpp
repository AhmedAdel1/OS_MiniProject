#include "FCFS_Scheduler.h"

FCFS_Scheduler::FCFS_Scheduler(Process* arr, unsigned long Size,double contextTime, Statistics& Stat)
{
    vector<Interval> allIntervals;      /// this vector contains all the processed intervals after finishing all the processes.
                                        /// this vector will be graphed after scheduling.

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

    time = 0;
    double beginTime,endTime;

    while(!readyQueue.empty())
    {
        Process temp = readyQueue.front();      /// FCFS (first come first serve) : the first process to arrive, runs first.
        while(temp.getArrivalTime() > time)     /// wait until its time comes.
            time += TIMESTAMP;

        /// if reached here, then the first element in the queue starts now.
        /// in this algorithm, we run the entire process until it's done.

        beginTime = time;
        time += temp.getBurstTime();
        endTime = time;
        /// after running, store its interval in the vector allIntervals to graph later.
        Interval Inter(beginTime,endTime,temp.getProcessID());
        allIntervals.push_back(Inter);

        time += contextTime;
        Interval ContextInter(endTime,endTime + contextTime,-1);      /// pushing the context switching interval.
        allIntervals.push_back(ContextInter);

        /// we need to calculate and store its : waiting time, turnaround time, weighted turnaround time.
        processInfo PI;
        PI.ID = temp.getProcessID();
        PI.TAT = time - temp.getArrivalTime();
        PI.waitingTime = PI.TAT - temp.getBurstTime();
        PI.wieghtedTAT = PI.TAT / temp.getBurstTime();

        finishedVector.push_back(PI);

        readyQueue.pop();
    }

    /// if we reached here, then all the ready queue processed and it's empty now.
    /// the useful info we have is : allIntervals vector (for graphing) + finishedVector (for statistics)
    /// we put them both in the statistics object passed in parameters.

    Stat.setGraphIntervals(allIntervals);
    Stat.setProcInfoVector(finishedVector);

    double AvgTAT = 0;
    double AvgWeightedTAT = 0;
    for(int i = 0; i < finishedVector.size(); i++)
    {
        AvgTAT += finishedVector[i].TAT;
        AvgWeightedTAT += finishedVector[i].wieghtedTAT;
    }
    AvgTAT/=Size;
    AvgWeightedTAT/=Size;
    //Stat.setAvgTurnaroundTime(AvgTAT);
    //Stat.setAvgWeightedWaitingTime(AvgWeightedTAT);
}

