#include "SRTN_Scheduler.h"

SRTN_Scheduler::SRTN_Scheduler(Process* arr, unsigned long Size)
{
    for(int i=0; i<Size; i++)
        readyQueue.push_back(arr[i]);

    clk = 0;
    finishedArr_index = 0;
    finishedArr = new processInfo[Size];

    int Min;
    int minIndex;
    while(!(readyQueue.empty() && running.empty()))
    {
        if(!readyQueue.empty() && readyQueue[0].getArrivalTime() <= clk)
        {
            running.push_back(readyQueue[0]);
            readyQueue.erase(readyQueue.begin());
        }

        if(!running.empty())
        {
            Min = running[0].getRemainingTime();
            minIndex = 0;
            for(int i=0; i<running.size(); i++)
            {
                if(running[i].getRemainingTime() < Min)
                {
                    Min = running[i].getRemainingTime();
                    minIndex = i;
                }
            }
            running[minIndex].setRemainingTime(Min-1);
            cout << Min-1 <<endl;
            if(Min-1 == 0)      /// the process finished
            {
                finishedArr[finishedArr_index].ID = running[minIndex].getProcessID();
                finishedArr[finishedArr_index].TAT = clk+1 - running[minIndex].getArrivalTime();
                finishedArr[finishedArr_index].waitingTime = finishedArr[finishedArr_index].TAT - running[minIndex].getBurstTime();
                finishedArr[finishedArr_index].wieghtedTAT = finishedArr[finishedArr_index].TAT / running[minIndex].getBurstTime();

                finishedArr_index++;
                running.erase(running.begin() + minIndex);
            }
        }
        clk++;
    }


    cout << "printing statistics \n";
    for(int i = 0; i < Size; i++)
    {
        cout << finishedArr[i].ID << "\t" << finishedArr[i].TAT << "\t" << finishedArr[i].waitingTime << "\t" << finishedArr[i].wieghtedTAT << endl;
    }

}

