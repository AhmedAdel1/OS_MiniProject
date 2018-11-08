#include "HPFScheduler.h"

HPFScheduler::HPFScheduler() {
}

Statistics HPFScheduler::schedule(Process arr[], int count,double contextTime) {

	myStatistics.clearStatistics();

	if (count <= 0)
		return myStatistics;

	//set context switch time
	this->contextTime = contextTime;

	//Create a copy from processes using pointers, to make operations faster
	Process** processes = new Process*[count];
	for (int i = 0; i < count; ++i) {
		processes[i] = new Process;
		processes[i]->setProcessID(arr[i].getProcessID());
		processes[i]->setArrivalTime(arr[i].getArrivalTime());
		processes[i]->setBurstTime(arr[i].getBurstTime());
		processes[i]->setPriority(arr[i].getPriority());
	}

	scheduleUtility(processes, count, contextTime);

	vector<double> turnAround = myStatistics.getTurnaroundTime();
	vector<double> waitingTime(count);
	vector<double> weightedWaitingTime(count);

	double avgWeightedWaitingTime = 0;
	double avgTurnAroundTime = 0;

	for (int i = 0; i < count; ++i) {

		//Waiting Time = TurnAround - Arrival Time
		waitingTime[i] = turnAround[i] - arr[i].getArrivalTime();

		//Weighted Waiting Time = (Waiting Time)/(Running Time)
		weightedWaitingTime[i] = waitingTime[i]/arr[i].getBurstTime();


		avgWeightedWaitingTime += weightedWaitingTime[i];

		avgTurnAroundTime += turnAround[i];
	}

	avgTurnAroundTime /= count;
	avgWeightedWaitingTime /= count;

	myStatistics.setWaitingTime(waitingTime);
	myStatistics.setWeightedWaitingTime(weightedWaitingTime);
	myStatistics.setAvgTurnaroundTime(avgTurnAroundTime);
	myStatistics.setAvgWeightedWaitingTime(avgWeightedWaitingTime);

	//Clean up
	for (int i = 0; i < count; ++i)
		delete processes[i];
	delete processes;

	return myStatistics;
}

void HPFScheduler::scheduleUtility(Process* processes[], int count,
		double contextTime) {
	//clear ready queue and fill it with the processes
	readyQueue.assign(processes, processes + count);

	//Turn around for statistics
	vector<double> turnAround(count);
	//Graph Intervals for plotting
	vector<Interval> graphIntervals;

	//sort ready queue by arrival time (equivalent to real arrival system, when it arrives, it's inserted)
	//note that it's sorted in reversed order, so I can pop from back
	sort(readyQueue.begin(), readyQueue.end(),
			[](const auto p1, const auto p2) {
				if(p1->getArrivalTime() != p2->getArrivalTime())
				return p1->getArrivalTime() > p2->getArrivalTime();
				else
				return p1->getProcessID() > p2->getProcessID();
			});

	unsigned long currentProcessID = 0;
	while (!pq.empty()) //remove old values from priority queue ( if there's any )
		pq.pop();

	double currentTime = 0; //current time stamp

	//current process reference
	Process* currentProcess = NULL;

	double inCPUTime = 0; //how long this process is being processed
	while (!pq.empty() || !readyQueue.empty()) {
		if (!readyQueue.empty()
				&& currentTime > readyQueue.back()->getArrivalTime()) //if elements arrived at ready queue
						{
			pq.push(readyQueue.back());
			readyQueue.pop_back();
		}

		if (!pq.empty()) { //there's element to be scheduled
			if (currentProcessID == pq.top()->getProcessID()) { //current process is under scheduling(no one arrived with higher priority)

				currentProcess = pq.top();

				currentTime += TIMESTAMP;
				inCPUTime += TIMESTAMP;

				//if the process is done, remove it from cpu
				if (currentProcess->getBurstTime() <= 0) {

					turnAround[currentProcessID - 1] = currentTime
							- currentProcess->getArrivalTime();
					pq.pop();

					Interval processInterval = Interval(currentTime - inCPUTime,
							currentTime, currentProcessID);
					graphIntervals.push_back(processInterval);

					//Context switch
					double contextElapsedTime = 0;
					while (contextElapsedTime < contextTime) {
						contextElapsedTime += TIMESTAMP;
						currentTime += TIMESTAMP;
					}
					currentProcessID = 0;
				} else { //the process run for some time, decrease needed time
					currentProcess->setBurstTime(
							currentProcess->getBurstTime() - TIMESTAMP);
					currentTime += TIMESTAMP;
				}

			} else {
				//you took another process place
				if (currentProcessID != 0) {
					Interval processInterval = Interval(currentTime - inCPUTime,
							currentTime, currentProcessID);
					graphIntervals.push_back(processInterval);
					//Context switch
					double contextElapsedTime = 0;
					while (contextElapsedTime < contextTime) {
						contextElapsedTime += TIMESTAMP;
						currentTime += TIMESTAMP;
					}
				}
				inCPUTime = 0;
				currentProcessID = pq.top()->getProcessID();
				currentTime += TIMESTAMP;
			}
		} else { //wait for new process to arrive
			currentTime += TIMESTAMP;
		}
	}

	myStatistics.setTurnaroundTime(turnAround);
	myStatistics.setGraphIntervals(graphIntervals);
}

