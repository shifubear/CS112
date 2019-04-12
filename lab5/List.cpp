/* List.cpp contains the definitions of the methods in the List class.
 * List.cpp
 * Student Name: Shion Fukuzawa
 * Date: February 28, 2017
 */

#include "List.h"
#include <iostream>
using namespace std;

/*
 * Default constructor
 * Initializes all instance variables.
 */
List::List() {
	mySize = 0;
	myFirst = myLast = NULL;
}

/*
 * Private method for copying contents of an original list into a new list.
 *
 */
void List::makeCopyOf(const List& original) {
	if (original.getSize() > 0) {
		Node* oPtr = original.myFirst;
		while (oPtr != NULL) {
			append(oPtr->myItem);
			oPtr = oPtr->myNext;
		}
	}
}

/*
 * Copy constructor.
 * Creates a new list with the same values as original list.
 */
List::List(const List& original) {
	mySize = 0;
	myFirst = myLast = NULL;
	makeCopyOf(original);
}

/*
 * Default Node constructor.
 * Node is a private Struct defined in the list class.
 */
List::Node::Node() {
	myItem = Item();
	myNext = NULL;
}

/*
 * Explicit Node constructor.
 */
List::Node::Node(Item it, Node* next) {
	myItem = it;
	myNext = next;
}

/*
 * Destructor
 * This implementation of a list utilizes C++'s recursive destructor calls.
 */
List::~List() {
	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;
}

/*
 * Node struct destructor
 */
List::Node::~Node() {
//	cout << "~Node() is deallocating the node containing item " << myItem << endl;
	delete myNext;
	myNext = NULL;
}

/*
 * Getter for the first item stored in the list.
 */
Item List::getFirst() const {
	if (myFirst != NULL) {
		return myFirst->myItem;
	} else {
		throw underflow_error("Cannot access empty list!!");
	}
}

/*
 * Getter to get the last item stored in the list.
 */
Item List::getLast() const {
	if (myLast != NULL) {
		return myLast->myItem;
	} else {
		throw underflow_error("Cannot access empty list!!");
	}
}

/*
 * Assignment operator. Copies a list into another list.
 */
List& List::operator=(const List& original) {
	if (this == &original) {
		return *this;
	}

	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;

	makeCopyOf(original);

	return *this;
}

/*
 * Append adds a new node with desired item at the end of the list.
 */
void List::append(const Item& it) {
	Node* newNode = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = newNode;
	} else {
		myLast->myNext = newNode;
	}

	myLast = newNode;
	mySize++;
}

