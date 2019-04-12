/*
 * List.cpp defines the methods for a List class
 * CS 112
 *  Created on: Mar 7, 2017
 *      Author: isa3 (Ian Adams)
 */

#include "ListIan.h"

List::List() {
	//List default constructor
	mySize = 0;
	myFirst = myLast = NULL;
}

List::Node::Node() {
	//Node default constructor
	myNext = NULL;
	myItem = 0;
}

List::Node::Node(const Item& item, Node * next) {
	//Node explicit constructor
	myNext = next;
	myItem = item;
}

void List::append(const Item& it) {
	//adds a Node to the list with Item it and myNext NULL
	Node * tempPtr = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = tempPtr;
	} else {
		myLast->myNext = tempPtr;
	}
	myLast = tempPtr;
	mySize++;
}

unsigned List::getSize() const {
	//returns the length of the list
	return mySize;
}

Item List::getFirst() const {
	//returns the item of the first node
	if (mySize != 0) {
		return myFirst->myItem;
	} else {
		throw underflow_error("Empty List");
	}

}

Item List::getLast() const {
	//returns the item of the last node
	if (mySize != 0) {
		return myLast->myItem;
	} else {
		throw underflow_error("Empty List");
	}
}

List::List(const List& original) {
	//copy constructor
	mySize = 0;
	myFirst = myLast = NULL;
	if ( original.mySize > 0) {
		Node * oPtr = original.myFirst;
		while (oPtr != NULL) {
			append(oPtr->myItem);
			oPtr = oPtr->myNext;
		}
	}
}

List& List::operator=(const List& original) {
	//assignment operator
	if (this != &original) {
		delete myFirst;
		mySize = 0;
		myFirst = myLast = NULL;
		if ( original.mySize > 0) {
			Node * oPtr = original.myFirst;
			while (oPtr != NULL) {
				append(oPtr->myItem);
				oPtr = oPtr->myNext;
			}
		}
	}
	return *this;
}

/* operator!=
* @param: List&, a reference to the list being compared
* Return: Boolean
* written by Ian Adams (isa3)
*/
bool List::operator!=(const List& original) const {
	if (original.mySize != 0) {
		if (original.mySize == mySize) {
			Node * oPtr = original.myFirst;
			Node * myPtr = myFirst;
			while (oPtr != NULL) {
				if (oPtr->myItem != myPtr->myItem) {
					return true;
				} else {
					oPtr = oPtr->myNext;
					myPtr = myPtr->myNext;
				}
			}
			return false;
		}
		return true;
	} else {
		if ( mySize == 0) {
			return false;
		}
		return true;
	}
}

/* getIndexOf
* @param: Item&, of which the index in the list is being found
* Return: Integer, the index
* written by Ian Adams (isa3)
*/
int List::getIndexOf(const Item& it) const {
	if (mySize != 0) {
		Node * myPtr = myFirst;
		int index = 0;
		while (myPtr != NULL) {
			if( myPtr->myItem == it) {
				return index;
			}
			index++;
			myPtr = myPtr->myNext;
		}
	}
	return -1;
}

/* remove
* @param: int index, the index whose Node will be removed from the list
* Return: Item, the item at that Node in the list
* written by Ian Adams (isa3)
*/
Item List::remove(int index) {
	if (mySize != 0) {
		Item item;
		Node * myPtr = myFirst;
		if (index < 1) {
			myPtr = myFirst->myNext;
			myFirst->myNext = NULL;
			item = myFirst->myItem;
			delete myFirst;
			myFirst = myPtr;
		} else if (index > (int)(mySize - 1)) {
			while (myPtr->myNext->myNext != NULL) {
				myPtr = myPtr->myNext;
			}
			myLast = myPtr;
			item = myLast->myNext->myItem;
			delete myLast->myNext;
			myLast->myNext = NULL;
		} else {
			for (int i=0; i < (index-1); i++) {
				myPtr = myPtr->myNext;
			}
			Node * deletePtr = myPtr->myNext;
			myPtr->myNext = myPtr->myNext->myNext;
			deletePtr->myNext = NULL;
			item = deletePtr->myItem;
			delete deletePtr;
		}
		mySize--;
		return item;
	} else {
		throw range_error("Empty list.");
	}
}

/* writeTo
* @param: ostream&, the stream being written to
* Return: none
* written by Ian Adams (isa3)
*/
void List::writeTo(ostream& out) const {
	Node * myPtr = myFirst;
	while (myPtr != NULL) {
		out << myPtr->myItem << "\t" << flush;
		myPtr = myPtr->myNext;
	}
}

void List::readFrom(istream& in) {
	while (true) {
		Item value;
		char c;
		in >> value;
		append(value);
		in.get(c);
		if (c == '\n') { break;	}
	}
}

/* readFrom
* @param: string&, the fileName being read from
* Return: none
* written by Ian Adams (isa3)
*/
void List::readFrom(const string& fileName) {
	ifstream fin(fileName.c_str());
	assert(fin.is_open());
	readFrom(fin);
	fin.close();
}

List::~List() {
	//list destructor
	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;
}

List::Node::~Node() {
	//node destructor
//	cout << "~Node() is deallocating the node containing item "
//			<< myItem << endl;
	delete myNext;
}

