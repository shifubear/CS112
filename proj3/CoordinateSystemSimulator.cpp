/*
 * CoordinateSystemSimulator.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: sf27
 */

#include "CoordinateSystemSimulator.h"
#include "Vec.h"
#include <iostream>
using namespace std;

CoordinateSystemSimulator::CoordinateSystemSimulator() {
	dimensions = 0;
}

void CoordinateSystemSimulator::getDimensions() {
	while (dimensions == 0) {
		cout << "Please input the number of dimensions in your space (Must be greater than 0) -> " << flush;
		cin >> dimensions;
	}
}

void CoordinateSystemSimulator::setStartPosition() {
	startPos = Vec(dimensions);
	while (true) {
		cout << "Please input the starting position." << endl;
		for (unsigned i = 0; i < dimensions; i++) {
			cout << "Position at startPos[" << i << "] -> " << flush;
			cin >> startPos[i];
		}
		cout << "Is this the position you would like to start at? [" << flush;
		for (unsigned i = 0; i < dimensions; i++) {
			cout << startPos[i] << flush;
			if (i != dimensions-1)
				cout << ", " << flush;
		}
		cout << "] (y/n)" << endl;
		string answer;
		cin >> answer;
		if (answer == "y" || answer == "Y")
			break;
	}
}

void CoordinateSystemSimulator::run() {

	getDimensions();

	setStartPosition();

	while (addVec()) {
		cout << "Success!!" << endl;
	}

	printFinalPosition();
}

bool CoordinateSystemSimulator::addVec() {
	Vec newVec(dimensions);

	cout << "Enter the POSITIVE values of the vec you would like to add (enter -1 to terminate)" << endl;
	for (unsigned i = 0; i < dimensions; i++) {
		cout << "Value at newVec[" << i << "] is -> " << flush;
		cin >> newVec[i];
		if (newVec[i] < 0)
			return false;
	}

	cout << "Adding the Vec with values {" << flush;
	for (unsigned i = 0; i < dimensions; i++) {
		cout << newVec[i] << flush;
		if (i != dimensions-1)
			cout << ", " << flush;
	}
	cout << "}... " << endl;

	startPos = startPos + newVec;

	return true;
}

void CoordinateSystemSimulator::printFinalPosition() {
	cout << "The final position after adding all of these values is {" << flush;
	for (unsigned i = 0; i < dimensions; i++) {
		cout << startPos[i] << flush;
		if (i != dimensions-1)
			cout << ", " << flush;
	}
	cout << "}" << endl;

}
