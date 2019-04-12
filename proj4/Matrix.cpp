/* Matrix.cpp defines Matrix class methods.
 * Student Name: Shion Fukuzawa, Carlos
 * Date: February 28, 2017
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 *
 * operator!=(), readFrom(istream), writeTo(string), operator+()
 */

#include "Matrix.h"
#include <cassert>
#include <stdexcept>
#include <fstream>

/**
 * Default constructor.
 * Initializes size to 0, 0
 */
Matrix::Matrix() {
	myRows = myColumns = 0;
}

/**
 * Explicit constructor.
 * Sets the size of matrix to rows, columns.
 */
Matrix::Matrix(unsigned rows, unsigned columns) {
	myRows = rows;
	myColumns = columns;
	myVec.setSize(rows);
	for (unsigned i = 0; i < rows; i++) {
		myVec[i].setSize(columns);
	}
}

/**
 * + operator.
 * Adds two matrices together and returns the resulting matrix.
 * The size of the two matrices must match.
 */
Matrix Matrix::operator+(const Matrix& m2) const {
	if (myRows != m2.getRows()) {
		throw invalid_argument("The matrix sizes do not match!!");
	}
	if (myColumns != m2.getColumns()) {
		throw invalid_argument("The matrix sizes do not match!!");
	}
	Matrix newMatrix(myRows, myColumns);
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			newMatrix[i][j] = myVec[i][j] + m2[i][j];
		}
	}
	return newMatrix;
}

/**
 * - operator.
 * Subtracts a matrix from another and returns the resulting matrix.
 * The size of the two matrices must match.
 */
//Matrix Matrix::operator-(const Matrix& m2) const {
//
//}


/**
 * == operator.
 * Returns true if both matrices are the same.
 */
bool Matrix::operator==(const Matrix& m2) const {
	if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
		return false;
	} else {
		return myVec == m2.myVec;
	}
}

/**
 * != operator.
 * Returns true if both matrices are not the same.
 */
bool Matrix::operator!=(const Matrix& m2) const {
	if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
		return true;
	} else {
		return !(myVec == m2.myVec);
	}
}


/**
 * [] operator for reading.
 * Returns the Vec of Items at index i.
 */
const Vec<Item> Matrix::operator[](unsigned i) const {
	if (i < 0 && myRows < i) {
		throw range_error("Invalid index");
	}
	return myVec[i];
}

/**
 * [] operator for writing.
 */
Vec<Item>& Matrix::operator[](unsigned i) {
	if (i < 0 && myRows < i) {
		throw range_error("Invalid index");
	}
	return myVec[i];
}

/**
 * Reads information from an input stream.
 * The size of the input stream must match that of the matrix.
 */
void Matrix::readFrom(istream& in) {
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			in >> myVec[i][j];
		}
	}
}

/**
 * Reads information from a file.
 * The number of items in the file must match the size of the matrix to store in.
 */
void Matrix::readFrom(const string& fileName) {
	ifstream fin(fileName.c_str());
	assert( fin.is_open() );
	unsigned newRows, newColumns;
	fin >> newRows >> newColumns;
	if (newRows != myRows) {
		myRows = newRows;
		myVec.setSize(newRows);
	}
	if (newColumns != myColumns) {
		myColumns = newColumns;
		for (unsigned i = 0; i < myRows; i++) {
			myVec[i].setSize(myColumns);
		}
	}

	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			fin >> myVec[i][j];
		}
	}
}

/**
 * Writes contents of matrix into an output stream.
 */
//void Matrix::writeTo(ostream& out) const {
//
//}

/**
 * Writes contents of matrix into a file.
 */
void Matrix::writeTo(const string& fileName) const {
	ofstream fout(fileName.c_str());
	assert( fout.is_open() );
	fout << myRows << ' ' << myColumns << '\n';
	for (unsigned i = 0; i < myRows; i++) {
		for (unsigned j = 0; j < myColumns; j++) {
			fout << myVec[i][j] << ' ';
		}
		fout << '\n';
	}
	fout.close();
}

/**
 * Returns a new matrix whose columns are original's rows and rows are original's columns.
 */
//Matrix Matrix::getTranspose() const {
//
//}

