#include "Process.h"

Process::Process()
{
    //ctor
}

/// Getters
unsigned long getProcessID()
{
    return processID;
}

char getState()
{
    return state;
}

unsigned long getPriority()
{
    return priority;
}

unsigned long getArrivalTime()
{
    return arrivalTime;
}

unsigned long getBurstTime()
{
    return burstTime;
}


/// Setters
void setProcessID(unsigned long ID)
{
    this.processID = ID;
}

void setPriority(unsigned long pr)
{
    this.priority = pr;
}

void setArrivalTime(unsigned long arTime)
{
    this.arrivalTime = arTime;
}

void setBurstTime(unsigned long brTime)
{
    this.burstTime = brTime;
}

/// changing states
void Block()           /// move from RUNNING state to BLOCKED state.
{
    this.state = BLOCKED;
}

void Awaken()          /// move from BLOCKED state to READY state.
{
    this.state = READY;
}

void Switch()          /// move from RUNNING state to READY state.
{
    this.state = READY;
}

void Schedule()        /// move from READY state to RUNNING state.
{
    this.state = RUNNING;
}

Process::~Process()
{
    //dtor
}
