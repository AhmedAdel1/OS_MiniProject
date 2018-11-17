#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include "Process.h"
#include "Interval.h"
#include "FCFS_Scheduler.h"
#include "SRTN_Scheduler.h"
#include "Statistics.h"

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

    for(unsigned long i =0; i<Size; i++)
        cout << arr[i].getProcessID() << "\t" << arr[i].getArrivalTime() << "\t" << arr[i].getBurstTime() << "\t" << arr[i].getPriority() << "\t" << endl;

    std::sort(arr,arr+Size,comp);

    Statistics S;
    ///FCFS_Scheduler FCFS(arr,Size,S);   /// S now has all the required statistics and graph intervals to be graphed later.
    SRTN_Scheduler FCFS(arr,Size,S);

    vector<Interval> I = S.getGraphIntervals();
    vector<processInfo> PI = S.getProcInfoVector();

    cout << "printing statistics \n";
    for(int i = 0; i < PI.size(); i++)
    {
        cout << PI[i].ID << "\t" << PI[i].TAT << "\t"  << PI[i].waitingTime << "\t"  << PI[i].wieghtedTAT << endl;
    }
    ///graphIntervals(S.getGraphIntervals());

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
    ///for(int i=0; i<intervalsVector.size(); i++)
    ///{
    ///    cout << intervalsVector[i].l << intervalsVector[i].r << intervalsVector[i].processID << endl;
    ///}
}
