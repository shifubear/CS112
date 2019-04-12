/* Vec.h provides a simple vector class named Vec.
 * Student Name: Shion Fukuzawa
 * Date: February 21, 2017
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>
using namespace std;

typedef double Item;

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
	bool operator==(const Vec& v2);
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

#endif /*VEC_H_*/
