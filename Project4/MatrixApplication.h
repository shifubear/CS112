/*
 * MatrixApplication.h
 * Declaration of matrix application class.
 * Student: Shion Fukuzawa, Carlos Payer
 * Date: March 04, 2017
 */

#ifndef MATRIXAPPLICATION_H_
#define MATRIXAPPLICATION_H_

#include <string>

class MatrixApplication {
public:
	void run();
	void displayMenu();
	void readCommand();
	void readFileName();

	void addition();
	void subtraction();
	void transpose();

private:
	unsigned command;
	std::string fileName;
};

#endif /* MATRIXAPPLICATION_H_ */
