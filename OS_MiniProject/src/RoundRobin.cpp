#include "RoundRobin.h"

RoundRobinScheduler::RoundRobinScheduler() {
}

void RoundRobinScheduler::schedule(Process arr[], int count,double contextTime,double quantumTime, Statistics&  s) {

	myStatistics.clearStatistics();

	if (count <= 0)
		return;

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

	scheduleUtility(processes, count, contextTime,quantumTime);


	vector<double> turnAround = myStatistics.getTurnaroundTime();
	vector<double> waitingTime(count);
	vector<double> weightedTurnAround(count);


	for (int i = 0; i < count; ++i) {
        //Waiting Time = TurnAround - Running Time
		waitingTime[arr[i].getProcessID()-1] = turnAround[arr[i].getProcessID()-1] - arr[i].getBurstTime();

		//Weighted Waiting Time = (Waiting Time)/(Running Time)
		weightedTurnAround[arr[i].getProcessID()-1] = turnAround[arr[i].getProcessID()-1]/arr[i].getBurstTime();

	}

	myStatistics.setWaitingTime(waitingTime);
	myStatistics.setWeightedTurnAroundTime(weightedTurnAround);
	vector<processInfo> processInfoVec;

	for(int i=0; i<count; ++i)
		processInfoVec.push_back(processInfo{i+1,waitingTime[i],turnAround[i],weightedTurnAround[i]});

	myStatistics.setProcInfoVector(processInfoVec);

	//Clean up
	for (int i = 0; i < count; ++i)
		delete processes[i];
	delete processes;

	s = myStatistics;
}

void RoundRobinScheduler::scheduleUtility(Process* processes[], int count,double contextTime, double quantumTime) {
	readyQueue.assign(processes, processes + count); //fill ready queue with the processes

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
	while (!q.empty()) //remove old values from queue ( if there's any )
		q.pop();

	double currentTime = 0; //current time stamp
	double inCPUTime = 0; //how long this process is being processed
	while (!q.empty() || !readyQueue.empty()) {
		while (!readyQueue.empty()
				&& currentTime > readyQueue.back()->getArrivalTime()) //if elements arrived at ready queue
						{
			q.push(readyQueue.back());
			readyQueue.pop_back();
		}

		if (!q.empty()) { //there's element to be scheduled
			if (currentProcessID == q.front()->getProcessID()) { //current process is under scheduling

				currentTime += TIMESTAMP;
				inCPUTime += TIMESTAMP;

				Process* currentProcess = q.front();

				//TODO print current process on graph


				//if time quantum is finished, or the process is finished, remove it from queue
				//if there's only this process in quantum, leave it unless it's finished
				if (q.size() > 1 && inCPUTime >= quantumTime || currentProcess->getBurstTime() <= 0) {
					q.pop();

					Interval processInterval(currentTime - inCPUTime,currentTime, currentProcessID);
					graphIntervals.push_back(processInterval);

					//if the process isn't done yet, push it in the back
					if (currentProcess->getBurstTime() > 0) {
						currentProcess->setBurstTime(currentProcess->getBurstTime() - TIMESTAMP);
						q.push(currentProcess);
					}
					//If it's finished
					else{
						turnAround[currentProcessID-1] = currentTime - currentProcess->getArrivalTime();
					}

                    double contextElapsedTime = 0;

                    //wait for context switch
                    while (contextElapsedTime < contextTime) {
                        contextElapsedTime += TIMESTAMP;
                        currentTime += TIMESTAMP;
                    }
                    processInterval = Interval(currentTime-contextElapsedTime,currentTime,-1);
                    graphIntervals.push_back(processInterval);
					currentProcessID = 0;

				} else { //update needed time
					currentProcess->setBurstTime(currentProcess->getBurstTime() - TIMESTAMP);
				}

			} else { //start processing another process
				currentProcessID = q.front()->getProcessID();
				currentTime += TIMESTAMP;
				inCPUTime = 0;
			}

		} else { //wait for new process to arrive
			currentTime += TIMESTAMP;
		}
	}

	myStatistics.setGraphIntervals(graphIntervals);
	myStatistics.setTurnaroundTime(turnAround);
}

