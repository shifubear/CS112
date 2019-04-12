/*
 * List.h prototypes the methods for a list class
 * CS 112
 *  Created on: Mar 7, 2017
 *      Author: isa3
 */

#ifndef LISTIAN_H_
#define LISTIAN_H_

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cassert>
#include <stdexcept>
using namespace std;

typedef double Item;

class List {
public:
	List();
	List(const List& original);
	virtual ~List();
	void append(const Item& it);
	unsigned getSize() const;
	Item getFirst() const;
	Item getLast() const;
	List& operator=(const List& original);
	bool operator!=(const List& original) const;
	int getIndexOf(const Item& it) const;
	Item remove(int index);
	void writeTo(ostream& out) const;
	void readFrom(istream& in);
	void readFrom(const string& fileName);
private:
	struct Node {
		Node();
		Node(const Item& item, Node * next);
		~Node();
		Item myItem;
		Node * myNext;
	};
	unsigned mySize;
	Node * myFirst;
	Node * myLast;
	friend class ListTester;
};

#endif /* LISTIAN_H_ */
