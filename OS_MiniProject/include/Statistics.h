#include <vector>
#include "Interval.h"
#include "processInfo.h"
using namespace std;

#ifndef STATISTICS_H_
#define STATISTICS_H_

class Statistics {
public:
	Statistics();

	const vector<Interval>& getGraphIntervals() const;
	void setGraphIntervals(const vector<Interval>& graphIntervals);

	const vector<processInfo>& getProcInfoVector() const;
	void setProcInfoVector(const vector<processInfo>& processInfoVec);

	const vector<double>& getTurnaroundTime() const;
	void setTurnaroundTime(const vector<double>& turnaroundTime);

	const vector<double>& getWaitingTime() const;
	void setWaitingTime(const vector<double>& waitingTime);

	const vector<double>& getWeightedTurnAroundTime() const;
	void setWeightedTurnAroundTime(const vector<double>& weightedTurnAroundTime);

	void clearStatistics();
private:

	vector<Interval> graphIntervals;
	vector<double> turnaroundTime;
	vector<double> waitingTime;
	vector<double> weightedTurnAroundTime;
	vector<processInfo> procInfoVector;
};

#endif /* STATISTICS_H_ */
