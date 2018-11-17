#include <vector>
#include "Interval.h"
#include "processInfo.h"
using namespace std;

#ifndef STATISTICS_H_
#define STATISTICS_H_

class Statistics {
public:
	Statistics();

	double getAvgTurnaroundTime() const;
	void setAvgTurnaroundTime(double avgTurnaroundTime);

	double getAvgWeightedWaitingTime() const;
	void setAvgWeightedWaitingTime(double avgWeightedWaitingTime);

	const vector<Interval>& getGraphIntervals() const;
	void setGraphIntervals(const vector<Interval>& graphIntervals);

	const vector<processInfo>& getProcInfoVector() const;
	void setProcInfoVector(const vector<processInfo>& processInfoVec);

	const vector<double>& getTurnaroundTime() const;
	void setTurnaroundTime(const vector<double>& turnaroundTime);

	const vector<double>& getWaitingTime() const;
	void setWaitingTime(const vector<double>& waitingTime);

	const vector<double>& getWeightedWaitingTime() const;
	void setWeightedWaitingTime(const vector<double>& weightedWaitingTime);

	void clearStatistics();
private:

	vector<Interval> graphIntervals;
	vector<double> turnaroundTime;
	vector<double> waitingTime;
	vector<double> weightedWaitingTime;
	vector<processInfo> procInfoVector;
	double avgTurnaroundTime;
	double avgWeightedWaitingTime;

};

#endif /* STATISTICS_H_ */
