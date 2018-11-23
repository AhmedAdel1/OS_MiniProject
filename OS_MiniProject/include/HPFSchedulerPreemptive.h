#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include "Process.h"
#include "Statistics.h"
using namespace std;

#ifndef HPFSchedulerPreemptive_H
#define HPFSchedulerPreemptive_H


class HPFSchedulerPreemptive {

public:
	HPFSchedulerPreemptive();
	Statistics schedule(Process processes[], int count, double contextTime);


private:
	//Utility function that does scheduling
	void scheduleUtility(Process* processes[], int count, double contextTime);

	//Time for transition between processes
	double contextTime;

	//Queue holds processes when it arrives
	vector<Process*> readyQueue;

	//Statistics about scheduler
	Statistics myStatistics;

	//comparator that priority queue will sort with
	struct PriorityComparator {
		//sort with highest priority, in case of tie, sort with lowest arrival time
		bool operator ()(Process* p1, Process* p2) const {
			int priority1 = p1->getPriority();
			int priority2 = p2->getPriority();
			if (priority1 == priority2)
				return p1->getArrivalTime() > p2->getArrivalTime(); //priority queue is max heap, reverse operator to make it correct
			else
				return priority1 < priority2; //lowest priority will be in the end
		}
	};
	//priority queue to get process with highest priority
	priority_queue<Process*, vector<Process*>, PriorityComparator> pq;

};

#endif
