#include "HPFScheduler.h"

HPFScheduler::HPFScheduler() {}


void HPFScheduler::schedule(Process* processes[], int count,
		double contextTime) {
	readyQueue.assign(processes, processes + count); //fill ready queue with the processes
	this->contextTime = contextTime;	//set context switch time

	//sort ready queue by arrival time (equivalent to real arrival system, when it arrives, it's inserted)
	//sort(readyQueue.begin(),
	//		readyQueue.end(), //note that it's sorted in reversed order, so I can pop from back
	//		[](const auto p1, const auto p2) {return p1->getArrivalTime() > p2->getArrivalTime();});

    /// when uncommenting these lines, an error occurs : invalid use of 'auto'

	unsigned long currentProcessID = 0;
	while (!pq.empty()) //remove old values from priority queue ( if there's any )
		pq.pop();

	auto prevClock = clock(); //reference to get time between operations

	double currentTime = 0; //current time stamp

	while (!pq.empty() || !readyQueue.empty()) {
		if (!readyQueue.empty()&& currentTime > readyQueue.back()->getArrivalTime()) //if elements arrived at ready queue
		{
			pq.push(readyQueue.back());
			readyQueue.pop_back();
		}

		if (!pq.empty()) { //there's element to be scheduled
			if (currentProcessID == pq.top()->getProcessID()) { //current process is under scheduling(no one arrived with higher priority)

				double elapsedTime = getTime(clock(), prevClock); //how long the process was in cpu

				Process* currentProcess = pq.top();

				//TODO print current process on graph
				currentTime += getTime(clock(), prevClock);
				prevClock = clock();

				if (elapsedTime >= currentProcess->getBurstTime()) { //if the process is done, remove it from cpu
					pq.pop();
				} else { //the process run for some time, decrease needed time
					currentProcess->setBurstTime(currentProcess->getBurstTime() - elapsedTime);
				}

			} else { //Context switch
				while (currentProcessID != 0
						&& getTime(clock(), prevClock) < (this->contextTime)) { //wait for context switch
					//TODO print context switch on graph
				}
				currentProcessID = pq.top()->getProcessID();
				currentTime += getTime(clock(), prevClock);
				prevClock = clock();
			}
		} else { //wait for new process to arrive
			currentTime += getTime(clock(), prevClock);
			prevClock = clock();
		}
	}
}

//Get time between clock c1 and c2 (c1>c2)
inline double HPFScheduler::getTime(const clock_t& c1, const clock_t& c2) {
	return (c1 - c2) / (1.0 * CLOCKS_PER_SEC);
}
