/*
 * Interval.h
 *
 *  Created on: Nov 6, 2018
 *      Author: Ahmed Ibrahim
 */

#ifndef INTERVAL_H_
#define INTERVAL_H_

struct Interval {
	double l;
	double r;
	int processID;
	Interval(double _l,double _r,int _processID){
		l = _l;
		r = _r;
		processID = _processID;
	}
};

#endif /* INTERVAL_H_ */
