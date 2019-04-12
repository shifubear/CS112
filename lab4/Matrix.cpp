/* Matrix.cpp defines Matrix class methods.
 * Student Name: Shion Fukuzawa
 * Date: February 28, 2017
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#include "Matrix.h"
#include <stdexcept>

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
