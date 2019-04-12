/*
 * MatrixApplication.cpp
 * Implementation of the matrix application class.
 * Student: Shion Fukuzawa, Carlos Payer
 * Date: March 04, 2017
 */

#include "Matrix.h"
#include "MatrixApplication.h"
#include <iostream>
using namespace std;

void printLine() {
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}

void MatrixApplication::run() {
	printLine();
	cout << "Welcome to the Matrix Application. " << endl;
	printLine();
	while (true) {
		displayMenu();
		readCommand();
		if (command < 0 || command > 3) {
			cout << "Invalid command... Try again! " << endl;
		}
		printLine();

		switch (command) {
		case 1:
			addition();
			break;
		case 2:
			subtraction();
			break;
		case 3:
			transpose();

			break;
		case 0:
			cout << "Good bye! " << endl;
			return;
		}

		printLine();
	}
}

void MatrixApplication::displayMenu() {
	cout << "Select a command from the following options: \n"
			<< "1. Addition \n"
			<< "2. Subtraction \n"
			<< "3. Transpose \n"
			<< "0. Quit\n"
			<< " > "
			<< flush;
}

void MatrixApplication::readCommand() {
	cin >> command;
}

void MatrixApplication::readFileName() {
	cout << "Please insert the file name -> " << flush;
	cin >> fileName;
}

void MatrixApplication::addition() {
	Matrix<double> m1;
	cout << "1 - " << flush;
	readFileName();
	m1.readFrom(fileName);

	Matrix<double> m2;
	cout << "2 - " << flush;
	readFileName();
	m2.readFrom(fileName);

	Matrix<double> result;
	result = m1 + m2;

	cout << endl << "The sum of these two matrices is " << endl;
	result.printMatrix();
}

void MatrixApplication::subtraction() {
	Matrix<double> m1;
	cout << "1 - " << flush;
	readFileName();
	m1.readFrom(fileName);

	Matrix<double> m2;
	cout << "2 - " << flush;
	readFileName();
	m2.readFrom(fileName);

	Matrix<double> result;
	result = m1 - m2;

	cout << endl << "The difference of these two matrices is " << endl;
	result.printMatrix();
}

void MatrixApplication::transpose() {
	Matrix<double> m1;
	readFileName();
	m1.readFrom(fileName);

	Matrix<double> result;
	result = m1.getTranspose();

	cout << endl << "The transposition of this matrix is " << endl;
	result.printMatrix();
}


