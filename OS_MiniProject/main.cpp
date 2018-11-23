#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "Process.h"
#include "Interval.h"
#include "FCFS_Scheduler.h"
#include "SRTN_Scheduler.h"
#include "Statistics.h"
#include "RoundRobin.h"
#include "HPFScheduler.h"

using namespace std;

void getProcesses(Process* arr,unsigned long Size,ifstream& myFile);
bool comp(Process p1, Process p2);

void graphIntervals(vector<Interval>);

int main(int argc, char** argv)
{
    ifstream myFile;
    myFile.open("output.txt",ios::in);

    unsigned long Size;
    myFile >> Size;        /// first line is the number of processes.
    cout << Size << endl;

    Process* arr = new Process[Size];
    getProcesses(arr,Size,myFile);

    //for(unsigned long i =0; i<Size; i++)
    //    cout << arr[i].getProcessID() << "\t" << arr[i].getArrivalTime() << "\t" << arr[i].getBurstTime() << "\t" << arr[i].getPriority() << "\t" << endl;

    std::sort(arr,arr+Size,comp);

    Statistics S;
    RoundRobinScheduler* hpf = new RoundRobinScheduler();
    hpf->schedule(arr,Size,1,10,S);


    vector<Interval> I = S.getGraphIntervals();
    vector<processInfo> PI = S.getProcInfoVector();

    double AvgTAT = 0;
    double AvgWeightedTAT = 0;
    cout << "printing statistics \n";
    for(int i = 0; i < PI.size(); i++)
    {
        AvgTAT += PI[i].TAT;
        AvgWeightedTAT += PI[i].wieghtedTAT;
        cout << "Process ID = " << PI[i].ID << "\tTurnAround Time = " << PI[i].TAT << "\tWaitingTime = "  << PI[i].waitingTime << "\tWeighted TurnAroundTime = "  << PI[i].wieghtedTAT << endl;
    }
    AvgTAT/=Size;
    AvgWeightedTAT/=Size;
    cout << "Average TAT = " << AvgTAT << "\t Average Weighted TAT = " << AvgWeightedTAT << endl;

    graphIntervals(S.getGraphIntervals());

    myFile.close();

    system("/usr/bin/python plot_intervals.py");
    return 0;
}

void getProcesses(Process* arr,unsigned long Size,ifstream& myFile)
{
    unsigned long prID;
    double prior,arrivTime,bursTime;
    for(unsigned long i = 0; i<Size; i++)
    {
        myFile >> prID >> arrivTime >> bursTime >> prior;

        arr[i].setProcessID(prID);
        arr[i].setArrivalTime(arrivTime);
        arr[i].setBurstTime(bursTime);
        arr[i].setRemainingTime(bursTime);
        arr[i].setPriority(prior);
    }
}

bool comp(Process p1, Process p2)
{
    return (p1.getArrivalTime() < p2.getArrivalTime());
}

void graphIntervals(vector<Interval> intervalsVector)
{
    /// todo : graph all the intervals (with python API)


    ofstream myIntervalsFile;
    myIntervalsFile.open("intervals.txt",ios::out);


    for(int i=0; i<intervalsVector.size(); i++)
    {
        ///cout << intervalsVector[i].processID << "\t" << intervalsVector[i].l << endl;
        ///cout << intervalsVector[i].processID << "\t" << intervalsVector[i].r << endl;

        myIntervalsFile << intervalsVector[i].processID << "\t" << intervalsVector[i].l << endl;
        myIntervalsFile << intervalsVector[i].processID << "\t" << intervalsVector[i].r << endl;
    }

    myIntervalsFile.close();
}
