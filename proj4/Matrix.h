/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name: Shion Fukuzawa
 * Date: February 28, 2017
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "Vec.h"

typedef double Item;

class Matrix {
public:
	// Constructors
	Matrix();
	Matrix(unsigned rows, unsigned columns);

	// Operators
	Matrix operator+(const Matrix& m2) const;
	Matrix operator-(const Matrix& m2) const;
	bool operator==(const Matrix& m2) const;
	bool operator!=(const Matrix& m2) const;
	const Vec<Item> operator[](unsigned i) const;
	Vec<Item>& operator[](unsigned i);

	// io operations
	void readFrom(istream& in);
	void readFrom(const string& fileName);
	void writeTo(ostream& out) const;
	void writeTo(const string& fileName) const;

	// Getters
	unsigned getRows() const { return myRows; }
	unsigned getColumns() const { return myColumns; }

	// Other operations
	Matrix getTranspose() const;

private:
	unsigned myRows;
	unsigned myColumns;
	Vec< Vec<Item> > myVec;

	friend class MatrixTester;
};


#endif
