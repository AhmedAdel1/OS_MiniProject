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


double Statistics::getAvgTurnaroundTime() const {
	return avgTurnaroundTime;
}

void Statistics::setAvgTurnaroundTime(double avgTurnaroundTime) {
	this->avgTurnaroundTime = avgTurnaroundTime;
}

double Statistics::getAvgWeightedWaitingTime() const {
	return avgWeightedWaitingTime;
}

void Statistics::setAvgWeightedWaitingTime(double avgWeightedWaitingTime) {
	this->avgWeightedWaitingTime = avgWeightedWaitingTime;
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

const vector<double>& Statistics::getWeightedWaitingTime() const {
	return weightedWaitingTime;
}

void Statistics::setWeightedWaitingTime(const vector<double>& weightedWaitingTime) {
	this->weightedWaitingTime = weightedWaitingTime;
}



void Statistics::clearStatistics() {
	graphIntervals.clear();
	turnaroundTime.clear();
	waitingTime.clear();
	weightedWaitingTime.clear();

	avgTurnaroundTime = 0;
	avgWeightedWaitingTime = 0;
}
