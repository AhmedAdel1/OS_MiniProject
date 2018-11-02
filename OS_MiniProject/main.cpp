#include <iostream>
#include <fstream>
#include "process.h"


using namespace std;

void getProcesses(Process* arr,unsigned long Size,ifstream& myFile);

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
        arr[i].setPriority(prior);
    }
}
