#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include "Process.h"

using namespace std;

#ifndef RoundRobinScheduler_H
#define RoundRobinScheduler_H

class RoundRobinScheduler {

public:
	RoundRobinScheduler();
	void schedule(Process* processes[], int count, double contextTime,double quantumTime); //TODO add GUI reference

private:
	double contextTime;
	double quantumTime;
	vector<Process*> readyQueue;

	//utility function to get time between 2 clocks
	inline double getTime(const clock_t& c1, const clock_t& c2);

	//current process in front, new process in back
	deque<Process*> deq;

};

#endif
