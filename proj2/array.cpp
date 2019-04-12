/* array.cpp defines "C style" array operations
 * Name: Shion Fukuzawa
 * Date: February 14, 2017
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 */
 
#include "array.h"
#include <fstream>
#include <cstdlib>

/* Initializes the array
 * @param: a, an array of doubles
 * @param: size, the size of the array
 * Postcondition: The array a should be initialized with values from 0 through size.
 */
void initialize(double *a, unsigned size) {
	int val = 0;
	for (unsigned i = 0; i < size; i++) {
		val = i+1;
		a[i] = val;
	}
}
 
/* Prints a given array
 * @param: a, an array of doubles
 * @param: size, the size of the array
 * Postcondition: Each value in the array should be printed to the console.
 */
void print(double *a, unsigned size) {
	for (unsigned i = 0; i < size; i++) {
		cout << *a << '\t';
		a++;
	}
}

/* Averages all values in a given array
 * @param: a, an array of doubles
 * @param: size, the size of the array
 * Postcondition: Return the average of each value in the array
 */
double average(double *a, unsigned size) {
	double total = 0;
	for (unsigned i = 0; i < size; i++) {
		total += *(a + i);
	}
	return total / size;
}

/* Adds all values in a given array
 * @param: a, an array of doubles
 * @param: size, the size of the array
 * Postcondition: Return the sum of each value in the array
 */
double sum(double *a, unsigned size) {
	double total = 0;
	for (unsigned i = 0; i < size; i++) {
		total += *(a + i);
	}
	return total;
}

/* Read values from a stream and store them in an array
 * @param: in, any input stream
 * @param: a, an array of doubles to store the values in
 * @param: size, the size of the array
 * Postcondition: Store each value from the input stream into the array
 */
void read(istream& in, double *a, int size) {
	for (int i = 0; i < size; i++) {
		in >> a[i];
	}
}

/* Read values from a textfile which has the number of items on the first line, then that many lines of values
 * @param: fileName, The name of the file to open
 * @param: a, The array to write to
 * @param: numValues, The size of the new array/The number of items in the textfile.
 * Postcondition: The array a should be filled with numValues values from fileName.
 */
void fill(const string& fileName, double* &a, int &numValues) {
	ifstream fin( fileName.c_str() );
	assert( fin.is_open() );

	fin >> numValues;
	delete [] a;
	a = new double[numValues];

	read(fin, a, numValues);
}

/* Changes the size of an array
 * @param: a, the array to change the size of.
 * @param: oldSize, the old size of the array a
 * @param: newSize, the desired new size of the array
 * Postcondition: If newSize is smaller or equal to oldSize, fill a with newSize values from the
 * 				  old array and truncate the rest. Otherwise copy all of the old values and fill the remaining
 * 				  space with 0s.
 */
void resize(double* &a, int oldSize, int newSize) {
	// Create new array
	double* newArray = new double[newSize];

	// If new size is smaller, copy old array but truncate overflowing values.
	if (newSize <= oldSize) {
		for (int i = 0; i < newSize; i++) {
			*(newArray + i) = *(a + i);
		}
	}
	// If new size is larger, copy old array then fill the rest of the space with 0s.
	else {
		for (int i = 0; i < oldSize; i++) {
			*(newArray + i) = *(a + i);
		}
		for (int i = oldSize; i < newSize; i++) {
			*(newArray + i) = 0;
		}
	}

	delete [] a;
	a = newArray;
}

/* Concatenates two arrays
 * @param: a1, the first array
 * @param: size1, the size of the first array
 * @param: a2, the second array
 * @param: size2, the size of the second array
 * @param: a3, the resulting array after combining a1 and a2.
 * @param: size3, the sum of size1 and size2.
 * Postcondition: a3 should be a new array with size3 including all elements from a1 followed by those in a2.
 */
void concat(double *a1, int size1, double *a2, int size2, double *&a3, int &size3) {
	size3 = size1 + size2;
	delete [] a3;
	a3 = new double[size3];
	for (int i = 0; i < size1; i++) {
		*(a3 + i) = *(a1 + i);
	}
	for (int i = 0; i < size2; i++) {
		*(a3 + size1 + i) = *(a2 + i);
	}
}

