/*
 * Statistics.cpp
 *
 *  Created on: Nov 8, 2018
 *      Author: Ahmed Ibrahim
 */

#include "Statistics.h"

Statistics::Statistics() {
	clearStatistics();
}

const vector<Interval>& Statistics::getGraphIntervals() const {
	return graphIntervals;
}

void Statistics::setGraphIntervals(const vector<Interval>& graphIntervals) {
	this->graphIntervals = graphIntervals;
}


const vector<processInfo>& Statistics::getProcInfoVector() const
{
    return procInfoVector;
}

void Statistics::setProcInfoVector(const vector<processInfo>& processInfoVec)
{
    this->procInfoVector = processInfoVec;
}



const vector<double>& Statistics::getTurnaroundTime() const {
	return turnaroundTime;
}

void Statistics::setTurnaroundTime(const vector<double>& turnaroundTime) {
	this->turnaroundTime = turnaroundTime;
}

const vector<double>& Statistics::getWaitingTime() const {
	return waitingTime;
}

void Statistics::setWaitingTime(const vector<double>& waitingTime) {
	this->waitingTime = waitingTime;
}

const vector<double>& Statistics::getWeightedTurnAroundTime() const {
	return weightedTurnAroundTime;
}

void Statistics::setWeightedTurnAroundTime(const vector<double>& weightedTurnAroundTime) {
	this->weightedTurnAroundTime = weightedTurnAroundTime;
}



void Statistics::clearStatistics() {
	graphIntervals.clear();
	turnaroundTime.clear();
	waitingTime.clear();
	weightedTurnAroundTime.clear();
	procInfoVector.clear();

}
