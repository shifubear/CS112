/*
 * CoordinateSystemSimulator.h
 *
 *  Created on: Feb 24, 2017
 *      Author: sf27
 */

#ifndef COORDINATESYSTEMSIMULATOR_H_
#define COORDINATESYSTEMSIMULATOR_H_

#include "Vec.h"

class CoordinateSystemSimulator {
public:
	CoordinateSystemSimulator();

	void run();
	void getDimensions();
	void setStartPosition();
	bool addVec();
	void printFinalPosition();

private:
	unsigned dimensions;
	Vec startPos;
};

#endif /* COORDINATESYSTEMSIMULATOR_H_ */
