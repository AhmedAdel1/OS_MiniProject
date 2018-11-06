#include "RoundRobin.h"

RoundRobinScheduler::RoundRobinScheduler() {
}

void RoundRobinScheduler::schedule(Process* processes[], int count,
		double contextTime, double quantumTime) {
	readyQueue.assign(processes, processes + count); //fill ready queue with the processes
	this->contextTime = contextTime;	//set context switch time

	//sort ready queue by arrival time (equivalent to real arrival system, when it arrives, it's inserted)
	//sort(readyQueue.begin(),
	//		readyQueue.end(), //note that it's sorted in reversed order, so I can pop from back
	//		[](const auto p1, const auto p2) {return p1->getArrivalTime() > p2->getArrivalTime();});

	unsigned long currentProcessID = 0;
	while (!deq.empty()) //remove old values from queue ( if there's any )
		deq.pop_back();

	auto prevClock = clock(); //reference to get time between operations

	double currentTime = 0; //current time stamp
	double inCPUTime = 0; //how long this process is being processed
	while (!deq.empty() || !readyQueue.empty()) {
		if (!readyQueue.empty()&& currentTime > readyQueue.back()->getArrivalTime()) //if elements arrived at ready queue
		{
			deq.push_back(readyQueue.back());
			readyQueue.pop_back();
		}

		if (!deq.empty()) { //there's element to be scheduled
			if (currentProcessID == deq.front()->getProcessID()) { //current process is under scheduling

				double elapsedTime = getTime(clock(), prevClock); //how long the process was in cpu

				inCPUTime += elapsedTime;

				Process* currentProcess = deq.front();

				//TODO print current process on graph
				currentTime += getTime(clock(), prevClock);

				prevClock = clock();

				//if time quantum is finished, or the process is finished, remove it from dequeue
				//if there's only this process in quantum, leave it unless it's finished
				if (deq.size() > 1 && inCPUTime >= quantumTime || elapsedTime >= currentProcess->getBurstTime()) {
					deq.pop_front();
					while (!deq.empty() && getTime(clock(), prevClock) < (this->contextTime)) { //wait for context switch
						//TODO print context switch on graph

					}
					currentProcessID = 0;
					currentTime += getTime(clock(), prevClock);
					if (elapsedTime < currentProcess->getBurstTime()) { //if the process isn't done yet, push it in the back
						currentProcess->setBurstTime(currentProcess->getBurstTime() - elapsedTime);
						deq.push_back(currentProcess);
					}
				} else { //update needed time
					currentProcess->setBurstTime(currentProcess->getBurstTime() - elapsedTime);
				}

				prevClock = clock();
			} else { //start processing another process
				currentProcessID = deq.front()->getProcessID();
				currentTime += getTime(clock(), prevClock);
				prevClock = clock();
				inCPUTime = 0;
			}

		} else { //wait for new process to arrive
			currentTime += getTime(clock(), prevClock);
			prevClock = clock();
		}
	}


}

//Get time between clock c1 and c2 (c1>c2)
inline double RoundRobinScheduler::getTime(const clock_t& c1,const clock_t& c2) {
	return (c1 - c2) / (1.0 * CLOCKS_PER_SEC);
}
