#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include "Process.h"
#include "Statistics.h"
using namespace std;

#ifndef RoundRobinScheduler_H
#define RoundRobinScheduler_H

class RoundRobinScheduler {

public:
	RoundRobinScheduler();
	void schedule(Process processes[], int count, double contextTime,double quantumTime,Statistics& s);

private:
	//Utility function that does scheduling
	void scheduleUtility(Process* processes[], int count, double contextTime,double quantumTime);

	//Time for transition between processes
	double contextTime;

	//Queue holds processes when it arrives
	vector<Process*> readyQueue;

	//Statistics about scheduler
	Statistics myStatistics;

	//current process in front, new process in back
	queue<Process*> q;

};

#endif
