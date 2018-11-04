#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include "Process.h"

using namespace std;

#ifndef HPFScheduler_H
#define HPFScheduler_H


class HPFScheduler {

public:
	HPFScheduler();
	void schedule(Process* processes[], int count, double contextTime); //TODO add GUI reference

private:
	double contextTime;
	vector<Process*> readyQueue;

	//utility function to get time between 2 clocks
	inline double getTime(const clock_t& c1, const clock_t& c2);

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
