#include "HPFScheduler.h"

HPFScheduler::HPFScheduler() {
}

void HPFScheduler::schedule(Process arr[], int count,double contextTime,Statistics & s) {

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

	scheduleUtility(processes, count, contextTime);

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

	s =  myStatistics;
}

void HPFScheduler::scheduleUtility(Process* processes[], int count,double contextTime) {
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

	while (!pq.empty()) //remove old values from priority queue ( if there's any )
		pq.pop();

	double currentTime = 0; //current time stamp

	//current process reference
	Process* currentProcess = NULL;
    unsigned long currentProcessID = 0;

	double inCPUTime = 0; //how long this process is being processed

	//While there's element to be scheduled (waiting for it's turn or will arrive soon)
	while (!pq.empty() || !readyQueue.empty()) {

		//if elements arrived at ready queue
		while (!readyQueue.empty()&& currentTime >= readyQueue.back()->getArrivalTime())
		{
			pq.push(readyQueue.back());
			readyQueue.pop_back();
		}

		if (!pq.empty()) { //there's element to be schedule
				currentProcess = pq.top();
                currentProcessID = currentProcess->getProcessID();

				pq.pop();

                inCPUTime = 0;
				currentTime += TIMESTAMP;
				inCPUTime += TIMESTAMP;

				//process it in the cpu
				while (inCPUTime < currentProcess->getBurstTime()) {
					inCPUTime += TIMESTAMP;
					currentTime += TIMESTAMP;
				}

				turnAround[currentProcessID - 1] = currentTime- currentProcess->getArrivalTime();


				Interval processInterval = Interval(currentTime - inCPUTime,currentTime, currentProcessID);
				graphIntervals.push_back(processInterval);

				//Context switch
				double contextElapsedTime = 0;
				while (contextElapsedTime < contextTime) {
					contextElapsedTime += TIMESTAMP;
					currentTime += TIMESTAMP;
				}
                processInterval = Interval(currentTime - contextElapsedTime,currentTime, -1);
				graphIntervals.push_back(processInterval);
		} else { //wait for new process to arrive
			currentTime += TIMESTAMP;
		}
	}

	myStatistics.setTurnaroundTime(turnAround);
	myStatistics.setGraphIntervals(graphIntervals);
}

