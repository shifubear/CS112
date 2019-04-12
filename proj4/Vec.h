/* Vec.h provides a simple vector class named Vec.
 * Student Name: Shion Fukuzawa
 * Date: February 21, 2017
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
#include <cassert>
#include <fstream>
using namespace std;

template <class Item>
class Vec {
public:
	Vec();
	Vec(unsigned size);
	Vec(const Vec& original);
	virtual ~Vec();
	
	Vec operator-(const Vec& operand);
	Vec operator+(const Vec& operand) const;
	double operator*(const Vec& operand) const;
	Vec& operator=(const Vec& original);
	bool operator==(const Vec& v2) const;
	bool operator!=(const Vec& v2);
	const Item operator[](unsigned index) const;
	Item& operator[](unsigned index);

	unsigned getSize() const { return mySize; }
	void setSize(unsigned newSize);

	Item* getArray() const { return myArray; }
	void setItem(unsigned index, const Item& it);
	Item getItem(unsigned index) const;

	void writeTo(ostream& out) const;
	void writeTo(const string& fileName) const;
	void readFrom(istream& in);
	void readFrom(const string& fileName);

private:
	unsigned mySize;
	Item*    myArray;
	friend class VecTester;
};


/* Default constructor
 * Postcondition: Sets mySize to 0 and myArray to NULL.
 */
template <class Item>
Vec<Item>::Vec() {
	mySize = 0;
	myArray = NULL;
}

/* Explicit constructor
 * @param: size, An unsigned integer.
 * Postcondition: Sets mySize to size and myArray to an array of size mySize. Each value of myArray will be the
 * 				  the default value of type Item.
 */
template <class Item>
Vec<Item>::Vec(unsigned size) {
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
template <class Item>
Vec<Item>::Vec(const Vec<Item>& original) {
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
template <class Item>
Vec<Item>::~Vec() {
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
template <class Item>
Vec<Item> Vec<Item>::operator-(const Vec<Item>& operand) {
	Vec<Item> newVec;
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
template <class Item>
Vec<Item> Vec<Item>::operator+(const Vec<Item>& operand) const {
	Vec<Item> newVec;
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
template <class Item>
double Vec<Item>::operator*(const Vec<Item>& operand) const {
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
template <class Item>
Vec<Item>& Vec<Item>::operator=(const Vec<Item>& original) {
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
template <class Item>
bool Vec<Item>::operator==(const Vec<Item>& v2) const {
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
template <class Item>
bool Vec<Item>::operator!=(const Vec<Item>& v2) {
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
template <class Item>
const Item Vec<Item>::operator[](unsigned index) const {
	if (myArray == NULL)
		throw range_error("The Vec is empty!!!");
	else if (index >= mySize)
		throw range_error("That is an invalid index for this array!!");

	return myArray[index];
}

/* Subscript operator to change a value at index.
 *
 */
template <class Item>
Item& Vec<Item>::operator[](unsigned index) {
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
template <class Item>
void Vec<Item>::setItem(unsigned index, const Item& it) {
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
template <class Item>
Item Vec<Item>::getItem(unsigned index) const {
	if (myArray == NULL)
		throw range_error("The Vec is empty!!!");
	else if (index >= mySize)
		throw range_error("That is an invalid index for this array!!");

	return myArray[index];
}

/* Changes the size of an existing Vec to newSize.
 * @param: newSize, the size to change to.
 */
template <class Item>
void Vec<Item>::setSize(unsigned newSize) {

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
template <class Item>
void Vec<Item>::writeTo(ostream& out) const {
	if (myArray == NULL)
		return;
	for (unsigned i = 0; i < mySize; i++) {
		out << myArray[i] << endl;
	}
}

/* Reads values from an istream and stores them into the Vec.
 * Precondition: The istream will only provide the number of values equal to mySize.
 */
template <class Item>
void Vec<Item>::readFrom(istream& in) {
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
template <class Item>
void Vec<Item>::readFrom(const string& fileName) {
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
template <class Item>
void Vec<Item>::writeTo(const string& fileName) const{
	ofstream fout(fileName.c_str());
	assert( fout.is_open() );
	fout << mySize << '\n';
	for (unsigned i = 0; i < mySize; i++) {
		fout << myArray[i] << '\n';
	}
	fout.close();
}


#endif /*VEC_H_*/
