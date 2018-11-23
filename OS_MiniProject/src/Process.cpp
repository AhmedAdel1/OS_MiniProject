#include "Process.h"

Process::Process()
{
    //ctor
}

/// Getters
unsigned long Process::getProcessID()
{
    return processID;
}

char Process::getState()
{
    return state;
}

double Process::getPriority()
{
    return priority;
}

double Process::getArrivalTime()
{
    return arrivalTime;
}

double Process::getBurstTime()
{
    return burstTime;
}

/// Setters
void Process::setProcessID(unsigned long ID)
{
    processID = ID;
}

void Process::setPriority(double pr)
{
    priority = pr;
}

void Process::setArrivalTime(double arTime)
{
    arrivalTime = arTime;
}

void Process::setBurstTime(double brTime)
{
    burstTime = brTime;
}


/// changing states
void Process::Block()           /// move from RUNNING state to BLOCKED state.
{
    state = BLOCKED;
}

void Process::Awaken()          /// move from BLOCKED state to READY state.
{
    state = READY;
}

void Process::Switch()          /// move from RUNNING state to READY state.
{
    state = READY;
}

void Process::Schedule()        /// move from READY state to RUNNING state.
{
    state = RUNNING;
}

void Process::setRemainingTime(double RT)
{
    remainingTime = RT;
}

double Process::getRemainingTime()
{
    return remainingTime;
}


Process::~Process()
{
    //dtor
}
