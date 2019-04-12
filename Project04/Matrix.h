/* Matrix.h provides a class for manipulating 2-dimensional vectors.
 * Student Name:
 * Date:
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */

#ifndef MATRIX
#define MATRIX

#include "Vec.h"

 template<class Item>

class Matrix {
public:
	Matrix();
	unsigned getRows() const;
	unsigned getColumns() const;
	Matrix(unsigned rows, unsigned columns);
	Vec<Item>& operator[](unsigned index);
	const Vec<Item>& operator[](unsigned index) const;
//	bool operator==(const Matrix& m2) const;
//	bool operator!=(const Matrix& m2) const;
//	void readFrom(istream& in);
//	void readFrom(const string& filename);
//	void writeTo(ostream& out) const;
//	void writeTo(const string& filename);
//	Matrix operator+(const Matrix& m2);
//	Matrix operator-(const Matrix& m2);
//	Matrix getTranspose();
private:
	unsigned         myRows;
	unsigned         myColumns;
	Vec< Vec<Item> > myVec;
	friend class MatrixTester;
};

 template<class Item>
 Matrix<Item>::Matrix() {
         myRows = myColumns = 0;
    }

 template<class Item>
 unsigned Matrix<Item>::getRows() const {
 	return myRows;
 }

 template<class Item>
 unsigned Matrix<Item>::getColumns() const {
 	return myColumns;
 }

 template<class Item>
 Matrix<Item>::Matrix(unsigned rows, unsigned columns) {
             myRows = rows;
             myColumns = columns;
             myVec.setSize(rows);
             for (unsigned i = 0; i < rows; i++) {
                 myVec[i].setSize(columns);
             }
    }

 template<class Item>
 Vec<Item>& Matrix<Item>::operator[](unsigned index) {
 	if(index>= myRows){
 		throw range_error("Error: Invalid index");
 	}
 	return myVec[index];
 }

 template<class Item>
 const Vec<Item>& Matrix<Item>::operator[](unsigned index) const{
 	if(index>= myRows){
 		throw range_error("Error: Invalid index");
 	}
 	return myVec[index];
 }

// bool Matrix::operator==(const Matrix& m2) const {
//       if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
//            return false;
//       } else {
//            return myVec == m2.myVec;
//       }
//    }
//
// bool Matrix::operator!=(const Matrix& m2) const {
//       if ( myRows != m2.getRows() || myColumns != m2.getColumns() ) {
//            return true;
//       } else {
//            return myVec != m2.myVec;
//       }
//    }
//
// void Matrix::readFrom(istream& in) {
// 	for (unsigned i = 0; i < myRows; i++) {
// 		for (unsigned j = 0; j < myColumns; j++) {
// 			in>> myVec[i][j];
// 		}
// 	}
// }
//
// void Matrix::readFrom(const string& filename){
// 	ifstream fin(filename.c_str());
// 	assert( fin.is_open() );
// 	fin >> myRows >> myColumns;
// 	myVec.setSize(myRows);
// 	for (unsigned i = 0; i < myRows; i++) {
// 	    myVec[i].setSize(myColumns);
// 	}
// 	for (unsigned i = 0; i < myRows; i++) {
// 		for (unsigned j = 0; j < myColumns; j++) {
// 			fin>> myVec[i][j];
// 		}
// 	}
// 	fin.close();
// }
//
// void Matrix::writeTo(ostream& out) const {
// 	for (unsigned i = 0; i < myRows; i++) {
// 		for (unsigned j = 0; j < myColumns; j++) {
// 			out << myVec[i][j] << " ";
// 		}
// 		out << endl;
// 	}
// }
//
// void Matrix::writeTo(const string& filename){
// 	ofstream fout(filename.c_str());
// 	assert( fout.is_open() );
// 	fout << myRows << " " << myColumns << endl;
// 	for (unsigned i = 0; i < myRows; i++) {
// 		for (unsigned j = 0; j < myColumns; j++) {
// 			fout << myVec[i][j] << " ";
// 		}
// 		fout << endl;
// 	}
// 	fout.close();
// }
//
// Matrix Matrix::operator+(const Matrix& m2) {
// 	if (myRows != m2.getRows() || myColumns != m2.getColumns() ){
// 		throw invalid_argument("Invalid arguments'size");
// 	}
// 	Matrix m(myRows, myColumns);
// 	if (myRows != 0 || myColumns != 0 ){
// 		for (unsigned i = 0; i < myRows; i++) {
// 			for (unsigned j = 0; j < myColumns; j++) {
// 				m[i][j] = myVec[i][j]+m2[i][j];
// 			}
// 		}
// 	}
// 	return m;
// }
//
// Matrix Matrix::operator-(const Matrix& m2) {
// 	if (myRows != m2.getRows() || myColumns != m2.getColumns() ){
// 		throw invalid_argument("Invalid arguments'size");
// 	}
// 	Matrix m(myRows, myColumns);
// 	if (myRows != 0 || myColumns != 0 ){
// 		for (unsigned i = 0; i < myRows; i++) {
// 			for (unsigned j = 0; j < myColumns; j++) {
// 				m[i][j] = myVec[i][j]-m2[i][j];
// 			}
// 		}
// 	}
// 	return m;
// }
//
// Matrix Matrix::getTranspose() {
// 	if (myRows != 0 && myColumns != 0 ){
// 		Matrix m(myColumns, myRows);
// 		for (unsigned i = 0; i < myRows; i++) {
// 			for (unsigned j = 0; j < myColumns; j++) {
// 				m[j][i] = myVec[i][j];
// 			}
// 		}
// 		return m;
// 	}
// 	Matrix m0;
// 	return m0;
// }

#endif
