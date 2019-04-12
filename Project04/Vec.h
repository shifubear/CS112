/* CS112 Lab01  Calvin College
 * Vec.h provides a simple vector class named Vec.
 *
 *  Created on: Feb 24, 2017
 *      Author: Carlos Payer Vivas (cp44)
 */

#ifndef VEC_H_
#define VEC_H_

#include <iostream>     // cout, cerr, ...
#include <fstream>      // ifstream, ofstream, ...
#include <string>
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // range_error, ...
using namespace std;

template<class Item>

class Vec {
public:
	Vec();
	Vec(unsigned size);
	Vec(const Vec<Item>& original);
	virtual ~Vec();
	Vec<Item>& operator=(const Vec<Item>& original);
	unsigned getSize() const;
	void setItem(unsigned index, const Item& it);
	Item getItem(unsigned index) const;
	void setSize(unsigned newSize);
	bool operator==(const Vec<Item>& v2)const;
	void writeTo(ostream& out) const;
	void readFrom(istream& in);
	Item& operator[](unsigned index);
	const Item& operator[](unsigned index) const;
	bool operator!=(const Vec<Item>& v2)const;
	void readFrom(const string& filename);
	void writeTo(const string& filename);
	Vec operator-(const Vec<Item>& v2);
	Vec operator+(const Vec<Item>& v2);
	double operator*(const Vec<Item>& v2);
private:
	unsigned mySize;
	Item *   myArray;
	friend class VecTester;
};

template<class Item>
Vec<Item>::Vec() {
	mySize=0;
	myArray=NULL;
}

template<class Item>
Vec<Item>::Vec(unsigned size) {
	mySize=size;
	if (size==0){
		myArray=NULL;
	}else{
		myArray= new Item[size]();
	}
}

template<class Item>
Vec<Item>::Vec(const Vec<Item>& original) {
	mySize = original.mySize;
	if (mySize==0){
		myArray=NULL;
	}else{
		myArray= new Item[mySize]();
		for (unsigned i = 0; i < mySize; i++) {
			myArray[i]=original.myArray[i];
		}
	}
}

template<class Item>
Vec<Item>::~Vec() {
	delete [] myArray;
	mySize=0;
	myArray=NULL;
}

template<class Item>
Vec<Item>& Vec<Item>::operator=(const Vec<Item>& original) {
	if (this!=&original){
		if (mySize!=original.mySize){
			if (mySize>0){
				delete [] myArray;
				myArray=NULL;
			}
			if (original.mySize>0){
				myArray= new Item[original.mySize]();
			}
			mySize=original.mySize;
		}
		for (unsigned i = 0; i < mySize; i++) {
			myArray[i]=original.myArray[i];
		}
	}
	return *this;
}

template<class Item>
unsigned Vec<Item>::getSize() const {
	return mySize;
}

template<class Item>
void Vec<Item>::setItem(unsigned index, const Item& it) {
	if (index>=mySize){
		throw range_error("Error: Invalid index");
	}else{
		myArray[index]=it;
	}
}

template<class Item>
Item Vec<Item>::getItem(unsigned index) const {
	if (index>=mySize){
			throw range_error("Error: Invalid index");
		}else{
			return myArray[index];
		}
}

template<class Item>
void Vec<Item>::setSize(unsigned newSize) {
	if (mySize != newSize) {
		if (newSize == 0) {
			delete [] myArray;
			myArray = NULL;
			mySize = 0;
		} else {
			Item* newArray;
			newArray = new Item[newSize]();
			for (unsigned i = 0; i < newSize; i++) {
				if (i<mySize){
					newArray[i]=myArray[i];
				}else{
					newArray[i]=0;
				}
			}
			mySize=newSize;
			delete [] myArray;
			myArray=newArray;
		}
	}
  }

template<class Item>
bool Vec<Item>::operator==(const Vec<Item>& v2) const{
	if (mySize!=v2.mySize) {
		return false;
	}
	for (unsigned i = 0; i < mySize; i++) {
		if (v2.myArray[i]!=myArray[i]){
			return false;
		}
	}
	return true;
}

template<class Item>
void Vec<Item>::writeTo(ostream& out) const {
	for (unsigned i = 0; i < mySize; i++) {
			out << myArray[i] << endl;;
	}
  }

template<class Item>
void Vec<Item>::readFrom(istream& in) {
	for (unsigned i = 0; i < mySize; i++) {
		in >> myArray[i];
	}
}

template<class Item>
Item& Vec<Item>::operator[](unsigned index) {
	if(index>= mySize){
		throw range_error("Error: Invalid index");
	}
	return myArray[index];
}

template<class Item>
const Item& Vec<Item>::operator[](unsigned index) const{
	if(index>= mySize){
		throw range_error("Error: Invalid index");
	}
	return myArray[index];
}

template<class Item>
bool Vec<Item>::operator!=(const Vec<Item>& v2) const{
	if (mySize!=v2.mySize) {
		return true;
	}
	for (unsigned i = 0; i < mySize; i++) {
		if (v2.myArray[i]!=myArray[i]){
			return true;
		}
	}
	return false;
}

template<class Item>
Vec<Item> Vec<Item>::operator+(const Vec<Item>& v2) {
	if (mySize!=v2.mySize){
		throw invalid_argument("Invalid arguments'size");
	}
	Vec vs(mySize);
	if (mySize!=0){
		for (unsigned i = 0; i < mySize; i++) {
			vs[i]=myArray[i]+v2[i];
		}
	}
	return vs;
}

template<class Item>
Vec<Item> Vec<Item>::operator-(const Vec<Item>& v2) {
	if (mySize!=v2.mySize){
		throw invalid_argument("Invalid arguments'size");
	}
	Vec vs(mySize);
	if (mySize!=0){
		for (unsigned i = 0; i < mySize; i++) {
			vs[i]=myArray[i]-v2[i];
		}
	}
	return vs;
}

template<class Item>
double Vec<Item>::operator*(const Vec<Item>& v2){
	if (mySize!=v2.mySize){
		throw invalid_argument("Invalid arguments'size");
	}
	double dp=0;
	if (mySize!=0){
		for (unsigned i = 0; i < mySize; i++) {
			dp=dp+myArray[i]*v2[i];
		}
	}
	return dp;
}

template<class Item>
void Vec<Item>::readFrom(const string& filename){
	ifstream fin(filename.c_str());
	assert( fin.is_open() );
	delete [] myArray;
	fin>>mySize;
	myArray = new Item[mySize];
	for (unsigned i = 0; i < mySize; i++) {
		fin>> myArray[i];
	}
	fin.close();
}

template<class Item>
void Vec<Item>::writeTo(const string& filename){
	ofstream fout(filename.c_str());
	assert( fout.is_open() );
	fout<<mySize<<endl;;
	for (unsigned i = 0; i < mySize; i++) {
		fout<< myArray[i]<<endl;
	}
	fout.close();
}


#endif /*VEC_H_*/
