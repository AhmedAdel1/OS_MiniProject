#include <iostream>
#include <fstream>
#include <math.h>
#include "Process.h"
#include "FCFS_Scheduler.h"
#include "SRTN_Scheduler.h"


using namespace std;

void getProcesses(Process* arr,unsigned long Size,ifstream& myFile);
bool comp(Process p1, Process p2);

int main(int argc, char** argv)
{
    ifstream myFile;
    myFile.open(argv[1],ios::in);

    unsigned long Size;
    myFile >> Size;        /// first line is the number of processes.
    cout << Size << endl;

    Process* arr = new Process[Size];
    getProcesses(arr,Size,myFile);

    for(unsigned long i =0; i<Size; i++)
        cout << arr[i].getProcessID() << "\t" << arr[i].getArrivalTime() << "\t" << arr[i].getBurstTime() << "\t" << arr[i].getPriority() << "\t" << endl;

    std::sort(arr,arr+Size,comp);

    ///FCFS_Scheduler FCFS(arr,Size);
    SRTN_Scheduler FCFS(arr,Size);

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
        arr[i].setArrivalTime((int)round(arrivTime));
        arr[i].setBurstTime((int)round(bursTime));
        arr[i].setRemainingTime((int)round(bursTime));
        arr[i].setPriority(prior);
    }
}

bool comp(Process p1, Process p2)
{
    return (p1.getArrivalTime() < p2.getArrivalTime());
}
