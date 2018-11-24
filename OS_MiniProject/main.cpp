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

void getProcesses(Process* arr,unsigned long Size,double contextTime,ifstream& myFile);
bool comp(Process p1, Process p2);

void printStatistics(Statistics S);
void graphIntervals(vector<Interval>);

int main(int argc, char** argv)
{
    string fileName;
    double contextSwitch = 0;
    double timeQuantom = 0;

    cout << "Please enter the input .txt file containing the processes (full path with extension : 'folder/example.txt'): " << endl;
    cin >> fileName;
    cout << "Please enter the context switching time in seconds : " << endl;
    cin >> contextSwitch;

    cout << "Please choose a process scheduler." << endl;
    cout << "\tEnter 'h'for 'Non-Preemptive Highest Priority First. (HPF)'" << endl;
    cout << "\tOr, Enter 'f'for 'First Come First Served. (FCFS)'" << endl;
    cout << "\tOr, Enter 'r'for 'Round Robin with fixed time quantum. (RR)'" << endl;
    cout << "\tOr, Enter 's'for 'Preemptive Shortest Remaining Time Next. (SRTN)" << endl;

    ifstream myFile;
    myFile.open(fileName,ios::in);

    unsigned long Size;
    myFile >> Size;        /// first line is the number of processes.

    Process* arr = new Process[Size];
    getProcesses(arr,Size,contextSwitch,myFile);

    std::sort(arr,arr+Size,comp);

    Statistics S;

    char choise;
    cin >> choise;

    switch(choise)
    {
        case 'h':
        case 'H':
            {
            /// Non-Preemptive Highest Priority First. (HPF)
            HPFScheduler* HPF = new HPFScheduler();
            HPF->schedule(arr,Size,contextSwitch,S);
            break;
            }
        case 'f':
        case 'F':
            {
            /// First Come First Served. (FCFS)
            FCFS_Scheduler* FCFS = new FCFS_Scheduler(arr,Size,contextSwitch,S);
            break;
            }
        case 'r':
        case 'R':
            {
            /// Round Robin with fixed time quantum. (RR)
            RoundRobinScheduler* hpf = new RoundRobinScheduler();
            double quantomTime =0;
            cout << "Please enter the quantom time : ";
            cin >> quantomTime;
            hpf->schedule(arr,Size,contextSwitch,quantomTime,S);
            break;
            }
        case 's':
        case 'S':
            {
            /// Preemptive Shortest Remaining Time Next. (SRTN)
            SRTN_Scheduler* hpf = new SRTN_Scheduler(arr,Size,contextSwitch,S);
            break;
            }
        default :
            cout << "Wrong input!" << endl;
            break;

    }
    printStatistics(S);
    graphIntervals(S.getGraphIntervals());

    myFile.close();


    return 0;
}

void getProcesses(Process* arr,unsigned long Size,double contextTime,ifstream& myFile)
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

void printStatistics(Statistics S)
{
    ofstream myStatsFile;
    myStatsFile.open("finalStatistics.txt",ios::out);

    vector<Interval> I = S.getGraphIntervals();
    vector<processInfo> PI = S.getProcInfoVector();

    double AvgTAT = 0;
    double AvgWeightedTAT = 0;
    cout << "Statistics \n";
    for(int i = 0; i < PI.size(); i++)
    {
        AvgTAT += PI[i].TAT;
        AvgWeightedTAT += PI[i].wieghtedTAT;
        myStatsFile << "Process ID = " << PI[i].ID << "\tTurnAround Time = " << max(PI[i].TAT,0.) << "\tWaitingTime = "  << max(PI[i].waitingTime,0.) << "\tWeighted TurnAroundTime = "  << max(PI[i].wieghtedTAT,0.) << endl;
    }
    if(PI.size()){
    AvgTAT/=PI.size();
    AvgWeightedTAT/=PI.size();
    }
    myStatsFile << "Average TAT = " << max(AvgTAT,0.) << "\t Average Weighted TAT = " << max(AvgWeightedTAT,0.) << endl;

    myStatsFile.close();

}

void graphIntervals(vector<Interval> intervalsVector)
{

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

    /// run the python script for plotting the intervals.
    system("python3 plot_intervals.py");
}
