/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student: Shion Fukuzawa, Carlos Payer
 * Date: March 04, 2017
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 *
 * operator!=(), readFrom(istream), writeTo(string), operator+()   by Shion Fukuzawa
 * writeTo(ostream), readFrom(string), operator-(), getTranspose() by Carlos Payer
 */

#ifndef MATRIX
#define MATRIX

#include "Vec.h"

 template<class Item>

class Matrix {
public:
	Matrix();
	Matrix(unsigned rows, unsigned columns);
	unsigned getRows() const;
	unsigned getColumns() const;
	void printMatrix() const;
	Vec<Item>& operator[](unsigned index);
	const Vec<Item>& operator[](unsigned index) const;
	Matrix<Item> operator+(const Matrix<Item>& m2);
	Matrix<Item> operator-(const Matrix<Item>& m2);
	bool operator==(const Matrix<Item>& m2) const;
	bool operator!=(const Matrix<Item>& m2) const;
	void readFrom(istream& in);
	void readFrom(const string& filename);
	void writeTo(ostream& out) const;
	void writeTo(const string& filename);
	Matrix<Item> getTranspose();
private:
	unsigned         myRows;
	unsigned         myColumns;
	Vec< Vec<Item> > myVec;
	friend class MatrixTester;
};

 /**
  * Default constructor.
  * Initializes size to 0, 0
  */
 template<class Item>
 Matrix<Item>::Matrix() {
	 myRows = myColumns = 0;
 }

 /**
  * Explicit constructor.
  * Sets the size of matrix to rows, columns.
  */
 template<class Item>
 Matrix<Item>::Matrix(unsigned rows, unsigned columns) {
	 myRows = rows;
	 myColumns = columns;
	 myVec.setSize(rows);
	 for (unsigned i = 0; i < rows; i++) {
		 myVec[i].setSize(columns);
	 }
 }

 /**
  * Returns the number of rows in the matrix.
  */
 template<class Item>
 unsigned Matrix<Item>::getRows() const {
 	return myRows;
 }

 /**
  * Returns the number of columns in the matrix.
  */
 template<class Item>
 unsigned Matrix<Item>::getColumns() const {
 	return myColumns;
 }

 /**
  * Prints the matrix beautifully. Good job us.
  */
 template<class Item>
 void Matrix<Item>::printMatrix() const {
	 for (unsigned i = 0; i < myRows; i++) {
		 if (i == 0) {
			 cout << "{" << flush;
		 } else {
			 cout << " " << flush;
		 }
		 for (unsigned j = 0; j < myColumns; j++) {
			 if (j == myColumns-1) {
				 cout << myVec[i][j] << flush;
			 } else {
				 cout << myVec[i][j] << ", " << flush;
			 }
		 }
		 if (i == myRows-1) {
			 cout << "}" << flush;
		 }
		 cout << endl;
	 }
 }

 /**
  * [] operator for writing.
  */
 template<class Item>
 Vec<Item>& Matrix<Item>::operator[](unsigned index) {
 	if(index>= myRows){
 		throw range_error("Error: Invalid index");
 	}
 	return myVec[index];
 }

 /**
  * [] operator for reading.
  * Returns the Vec of Items at index i.
  */
 template<class Item>
 const Vec<Item>& Matrix<Item>::operator[](unsigned index) const{
 	if(index>= myRows){
 		throw range_error("Error: Invalid index");
 	}
 	return myVec[index];
 }

 /**
  * + operator.
  * Adds two matrices together and returns the resulting matrix.
  * The size of the two matrices must match.
  */
 template<class Item>
 Matrix<Item> Matrix<Item>::operator+(const Matrix<Item>& m2) {
 	if (myRows != m2.getRows() || myColumns != m2.getColumns() ){
 		throw invalid_argument("Invalid arguments'size");
 	}
 	Matrix<Item> m(myRows, myColumns);
 	if (myRows != 0 || myColumns != 0 ){
 		for (unsigned i = 0; i < myRows; i++) {
 			for (unsigned j = 0; j < myColumns; j++) {
 				m[i][j] = myVec[i][j]+m2[i][j];
 			}
 		}
 	}
 	return m;
 }

 /**
  * - operator.
  * Subtracts a matrix from another and returns the resulting matrix.
  * The size of the two matrices must match.
  */
 template<class Item>
 Matrix<Item> Matrix<Item>::operator-(const Matrix<Item>& m2) {
 	if (myRows != m2.getRows() || myColumns != m2.getColumns() ){
 		throw invalid_argument("Invalid arguments'size");
 	}
 	Matrix<Item> m(myRows, myColumns);
 	if (myRows != 0 || myColumns != 0 ){
 		for (unsigned i = 0; i < myRows; i++) {
 			for (unsigned j = 0; j < myColumns; j++) {
 				m[i][j] = myVec[i][j]-m2[i][j];
 			}
 		}
 	}
 	return m;
 }

 /**
  * == operator.
  * Returns true if both matrices are the same.
  */
 template<class Item>
 bool Matrix<Item>::operator==(const Matrix<Item>& m2) const {
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
 template<class Item>
 bool Matrix<Item>::operator!=(const Matrix<Item>& m2) const {
       if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
            return true;
       } else {
            return myVec != m2.myVec;
       }
    }

 /**
  * Reads information from an input stream.
  * The size of the input stream must match that of the matrix.
  */
 template<class Item>
 void Matrix<Item>::readFrom(istream& in) {
 	for (unsigned i = 0; i < myRows; i++) {
 		for (unsigned j = 0; j < myColumns; j++) {
 			in>> myVec[i][j];
 		}
 	}
 }

 /**
  * Reads information from a file.
  * The number of items in the file must match the size of the matrix to store in.
  */
 template<class Item>
 void Matrix<Item>::readFrom(const string& filename){
 	ifstream fin(filename.c_str());
 	assert( fin.is_open() );
 	fin >> myRows >> myColumns;
 	myVec.setSize(myRows);
 	for (unsigned i = 0; i < myRows; i++) {
 	    myVec[i].setSize(myColumns);
 	}
 	for (unsigned i = 0; i < myRows; i++) {
 		for (unsigned j = 0; j < myColumns; j++) {
 			fin>> myVec[i][j];
 		}
 	}
 	fin.close();
 }

 /**
  * Writes contents of matrix into an output stream.
  */
 template<class Item>
 void Matrix<Item>::writeTo(ostream& out) const {
 	for (unsigned i = 0; i < myRows; i++) {
 		for (unsigned j = 0; j < myColumns; j++) {
 			out << myVec[i][j] << " ";
 		}
 		out << endl;
 	}
 }

 /**
  * Writes contents of matrix into a file.
  */
 template<class Item>
 void Matrix<Item>::writeTo(const string& filename){
 	ofstream fout(filename.c_str());
 	assert( fout.is_open() );
 	fout << myRows << " " << myColumns << endl;
 	for (unsigned i = 0; i < myRows; i++) {
 		for (unsigned j = 0; j < myColumns; j++) {
 			fout << myVec[i][j] << " ";
 		}
 		fout << endl;
 	}
 	fout.close();
 }

 /**
  * Returns a new matrix whose columns are original's rows and rows are original's columns.
  */
 template<class Item>
 Matrix<Item> Matrix<Item>::getTranspose() {
 	if (myRows != 0 && myColumns != 0 ){
 		Matrix<Item> m(myColumns, myRows);
 		for (unsigned i = 0; i < myRows; i++) {
 			for (unsigned j = 0; j < myColumns; j++) {
 				m[j][i] = myVec[i][j];
 			}
 		}
 		return m;
 	}
 	Matrix<Item> m0;
 	return m0;
 }

#endif
