/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Student Name: Shion Fukuzawa, Joyce Chew
 * Date: February 21, 2017
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 *
 * readFrom(file), operator-(), operator!=(), operator[]() written by Shion Fukuzawa
 * writeTo(file), operator+(), operator*() written by Joyce Chew
 */
 
#include "Vec.h"
#include <fstream>
#include <cassert>
#include <stdexcept>

/* Default constructor
 * Postcondition: Sets mySize to 0 and myArray to NULL.
 */
Vec::Vec() {
	mySize = 0;
	myArray = NULL;
}

/* Explicit constructor
 * @param: size, An unsigned integer.
 * Postcondition: Sets mySize to size and myArray to an array of size mySize. Each value of myArray will be the
 * 				  the default value of type Item.
 */
Vec::Vec(unsigned size) {
	mySize = size;
	if (size == 0) {
		myArray = NULL;
	} else {
		myArray = new Item[size];
		for (unsigned i = 0; i < size; i++) {
			myArray[i] = Item();
		}
	}
}

/* Copy constructor
 * @param: original, The Vec object to copy.
 * Postcondition: Sets mySize to original's size. If the size is 0, sets myArray to NULL. Otherwise copies each value
 * 				  from original into myArray
 */
Vec::Vec(const Vec& original) {
	mySize = original.getSize();
	if (mySize == 0) {
		myArray = NULL;
		return;
	}
	myArray = new Item[mySize];
	for (unsigned i = 0; i < mySize; i++) {
		myArray[i] = original.getArray()[i];
	}
}

/* Destructor
 * Postcondition: Deallocate memory used by myArray, then reset values of myArray and mySize
 */
Vec::~Vec() {
	delete [] myArray;
	myArray = NULL;
	mySize = 0;
}

/* Subtraction operator.
 * @param: operand, Another vec to subtract from the current Vec.
 * return: A new Vec with size mySize and values of Vec - operand at each index.
 *
 * Written by Shion Fukuzawa
 */
Vec Vec::operator-(const Vec& operand) {
	Vec newVec;
	if (myArray == NULL && operand.getArray() == NULL)
		return newVec;
	else if (mySize != operand.getSize())
		throw invalid_argument("The two Vecs must be the same size!");

	newVec.setSize(mySize);

	for (unsigned i = 0; i < mySize; i++) {
		newVec[i] = myArray[i] - operand[i];
	}

	return newVec;
}

/* Addition operator.
 * @param: operand, Another vac to add to the current Vec.
 * return: a new Vec with size mySize and the values of the current Vec + operand at each index.
 *
 * Written by Joyce Chew
 */

Vec Vec::operator+(const Vec& operand) const {
	Vec newVec;
	if (myArray == NULL && operand.getArray() == NULL) {
		return newVec;
	}
	else if (mySize != operand.getSize()) {
		throw invalid_argument("The two Vecs must be the same size!");
	}

	newVec.setSize(mySize);

	for (unsigned i = 0; i < mySize; i++) {
		newVec[i] = myArray[i] + operand[i];
	}

	return newVec;
}

/* dot product
 * @param: operand, a Vec to dot product with the current Vec
 * return: a double that is the sum of the products of the values of the current Vec and operand at each index
 *
 * Written by Joyce Chew
 */

double Vec::operator*(const Vec& operand) const {
	double result = 0;
	if (myArray == NULL && operand.getArray() == NULL) {
		return result;
	}
	else if (mySize != operand.getSize()) {
		throw invalid_argument("The two Vecs must be the same size!");
	}

	for (unsigned i = 0; i < mySize; i++) {
		result += myArray[i] * operand[i];
	}

	return result;

}

/* Assignment operator
 * @param: original, the Vec that is being assigned to the Vec.
 * @return: The vector that has had the original vec assigned to it.
 */
Vec& Vec::operator=(const Vec& original) {
	// Handle assignment of the exact same object;
	if (myArray == original.getArray()) {
		return *this;
	}

	// Get the size
	mySize = original.getSize();

	// Delete the old array
	delete [] myArray;

	// If the size is 0, set myArray to NULL and return
	if (mySize == 0) {
		myArray = NULL;
		return *this;
	}

	// Create a new array of size mySize
	myArray = new Item[mySize];
	// Assign each value from orinal to myArray;
	for (unsigned i = 0; i < mySize; i++) {
		myArray[i] = original.getArray()[i];
	}

	return *this;
}

/* Tests if two Vecs are the same.
 * return: true if equal, false if not.
 */
bool Vec::operator==(const Vec& v2) {
	if (mySize != v2.getSize())
		return false;

	for (unsigned i = 0; i < mySize; i++) {
		if (myArray[i] != v2.getItem(i))
			return false;
	}
	return true;
}

/* Tests if two Vecs are not the same.
 * return: true if not equal, false otherwise.
 *
 * Written by Shion Fukuzawa
 */
bool Vec::operator!=(const Vec& v2) {
	if (mySize != v2.getSize())
		return true;

	for (unsigned i = 0; i < mySize; i++) {
		if (myArray[i] != v2.getItem(i))
			return true;
	}
	return false;
}

/* Subscript operator for retrieval. Returns item at index of myArray.
 *
 */
const Item Vec::operator[](unsigned index) const {
	if (myArray == NULL)
		throw range_error("The Vec is empty!!!");
	else if (index >= mySize)
		throw range_error("That is an invalid index for this array!!");

	return myArray[index];
}

/* Subscript operator to change a value at index.
 *
 */
Item& Vec::operator[](unsigned index) {
	if (myArray == NULL)
		throw range_error("The Vec is empty!!!");
	else if (index >= mySize)
		throw range_error("That is an invalid index for this array!!");

	return myArray[index];
}

/* Sets the value of a particular item in a vec. Throws range error if the vec is empty or index is out of range.
 * @param: index, the index of the item to set the value of.
 * @param: it, the value to set the item to.
 * postcondition: The value at index should be set to it.
 */
void Vec::setItem(unsigned index, const Item& it) {
	if (myArray == NULL) {
		throw range_error("The Vec is empty!!!");
	}
	else if (index >= mySize) {
		throw range_error("That is an invalid index for this array!!");
	}

	myArray[index] = it;

}

/* Gets the item at desired index. Throws range error if the vec is empty or index is out of range.
 * @param: index, the index of the item to retrieve
 * @return: The value at index of myArray
 */
Item Vec::getItem(unsigned index) const {
	if (myArray == NULL)
		throw range_error("The Vec is empty!!!");
	else if (index >= mySize)
		throw range_error("That is an invalid index for this array!!");

	return myArray[index];
}

/* Changes the size of an existing Vec to newSize.
 * @param: newSize, the size to change to.
 */
void Vec::setSize(unsigned newSize) {

	Item* copy = new Item[newSize]();
	if (newSize == 0) {
		mySize = 0;
		delete [] myArray;
		myArray = NULL;
		return;
	}
	if (newSize > mySize) {
		for (unsigned i = 0; i < mySize; i++) {
			copy[i] = myArray[i];
		}
	} else if (newSize < mySize) {
		for (unsigned i = 0; i < newSize; i++) {
			copy[i] = myArray[i];
		}
	} else {
		delete [] copy;
		copy = NULL;
		return;
	}

	delete [] myArray;
	myArray = copy;
	mySize = newSize;
}

/* Writes values in the Vec to an ostream.
 */
void Vec::writeTo(ostream& out) const {
	if (myArray == NULL)
		return;
	for (unsigned i = 0; i < mySize; i++) {
		out << myArray[i] << endl;
	}
}

/* Reads values from an istream and stores them into the Vec.
 * Precondition: The istream will only provide the number of values equal to mySize.
 */
void Vec::readFrom(istream& in) {
	for (unsigned i = 0; i < mySize; i++) {
		in >> myArray[i];
	}
}

/* Reads values from a file and stores them into the Vec.
 * Precondition: The file will have the number of items on the first line, then that many lines of items.
 * 				 The files will not have more items than the size of myArray.
 *
 * Written by Shion Fukuzawa
 */
void Vec::readFrom(const string& fileName) {
	ifstream fin(fileName.c_str());
	assert( fin.is_open() );
	unsigned newSize;
	fin >> newSize;
	if (newSize != mySize)
		this->setSize(newSize);
	for (unsigned i = 0; i < newSize; i++) {
		fin >> myArray[i];
	}
	fin.close();
}

/* Reads the size and values of a Vec and stores them in a file.
 * Postcondition: The file has the size of the Vec on the first line.
 *                The file has all the values of Vec, in order, separated by new lines.
 */

void Vec::writeTo(const string& fileName) const{
	ofstream fout(fileName.c_str());
	assert( fout.is_open() );
	fout << mySize << '\n';
	for (unsigned i = 0; i < mySize; i++) {
		fout << myArray[i] << '\n';
	}
	fout.close();
}









