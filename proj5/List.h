/* List.h provides a class for storing information using a Linked List structure.
 * List.h
 * Student Name: Shion Fukuzawa (sf27), Ian Adams (isa3)
 * Date: March 11, 2017
 */

#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
using namespace std;

template <class Item>
class List {
public:
	List();
	List(const List& original);
	virtual ~List();

	unsigned getSize() const { return mySize; }
	Item getFirst() const;
	Item getLast() const;
	int getIndexOf(const Item& it) const;

	List<Item>& operator=(const List<Item>& original);
	bool operator==(const List<Item>& otherList);
	bool operator!=(const List<Item>& original) const;

	void append(const Item& it);
	void prepend(const Item& it);
	void insert(const Item& it, int index);
	Item remove(int index);

	void readFrom(istream& in);
	void writeTo(ostream& out) const;
	void readFrom(const string& fileName);
	void writeTo(const string& fileName);

private:
	struct Node {
		Node();
		Node(Item it, Node* next);
		~Node();
		Item  myItem;
		Node* myNext;
	};
	unsigned mySize;
	Node*    myFirst;
	Node*    myLast;

	void makeCopyOf(const List<Item>& original);

	friend class ListTester;
};

/*
 * Default constructor
 * Initializes all instance variables.
 */
template <class Item>
List<Item>::List() {
	mySize = 0;
	myFirst = myLast = NULL;
}

/*
 * Private method for copying contents of an original list into a new list.
 *
 */
template <class Item>
void List<Item>::makeCopyOf(const List<Item>& original) {
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
template <class Item>
List<Item>::List(const List<Item>& original) {
	mySize = 0;
	myFirst = myLast = NULL;
	makeCopyOf(original);
}

/*
 * Default Node constructor.
 * Node is a private Struct defined in the list class.
 */
template <class Item>
List<Item>::Node::Node() {
	myItem = Item();
	myNext = NULL;
}

/*
 * Explicit Node constructor.
 */
template <class Item>
List<Item>::Node::Node(Item it, Node* next) {
	myItem = it;
	myNext = next;
}

/*
 * Destructor
 * This implementation of a list utilizes C++'s recursive destructor calls.
 */
template <class Item>
List<Item>::~List() {
	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;
}

/*
 * Node struct destructor
 */
template <class Item>
List<Item>::Node::~Node() {
	//	cout << "~Node() is deallocating the node containing item " << myItem << endl;
	delete myNext;
	myNext = NULL;
}

/* getFirst()
 * Returns the first item stored in the list.
 */
template <class Item>
Item List<Item>::getFirst() const {
	if (myFirst != NULL) {
		return myFirst->myItem;
	} else {
		throw underflow_error("Cannot access empty list!!");
	}
}

/* getLast()
 * Returns the last item stored in the list.
 */
template <class Item>
Item List<Item>::getLast() const {
	if (myLast != NULL) {
		return myLast->myItem;
	} else {
		throw underflow_error("Cannot access empty list!!");
	}
}

/* getIndexOf
* @param: Item&, of which the index in the list is being found
* Return: Integer, the index
* written by Ian Adams (isa3)
*/
template <class Item>
int List<Item>::getIndexOf(const Item& it) const {
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

/*
 * Assignment operator. Copies a list into another list.
 */
template <class Item>
List<Item>& List<Item>::operator=(const List<Item>& original) {
	if (this == &original) {
		return *this;
	}

	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;

	makeCopyOf(original);

	return *this;
}

/* operator==
 * @param: Another list to compare this list to.
 * Returns true if the contents of both lists are the same.
 * written by Shion Fukuzawa (sf27)
 */
template <class Item>
bool List<Item>::operator==(const List<Item>& otherList) {
	if (mySize != otherList.getSize())
		return false;

	if (mySize == 0)
		return true;

	Node* myCurrent = myFirst;
	Node* otherCurrent = otherList.myFirst;

	while (myCurrent != NULL) {
		if (myCurrent->myItem != otherCurrent->myItem)
			return false;

		myCurrent = myCurrent->myNext;
		otherCurrent = otherCurrent->myNext;
	}

	return true;
}

/* operator!=
 * @param: List&, a reference to the list being compared
 * Return: Boolean
 * written by Ian Adams (isa3)
 */
template <class Item>
bool List<Item>::operator!=(const List<Item>& original) const {
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

/*
 * Append adds a new node with desired item at the end of the list.
 */
template <class Item>
void List<Item>::append(const Item& it) {
	Node* newNode = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = newNode;
	} else {
		myLast->myNext = newNode;
	}

	myLast = newNode;
	mySize++;
}

/*
 * Prepends a new node with desired item at the head of the list.
 * written by Shion Fukuzawa (sf27)
 */
template <class Item>
void List<Item>::prepend(const Item& it) {
	Node* newNode = new Node(it, NULL);
	if (mySize == 0) {
		myLast = newNode;
	} else {
		newNode->myNext = myFirst;
	}

	myFirst = newNode;
	mySize++;
}

/*
 * Inserts a new node with desired item at the specified index.
 * If the index is less than or equal to 0, the node will be prepended to the list.
 * If the index is greater than the size of the list, the node will be appended to the end of the list.
 * written by Shion Fukuzawa (sf27)
 */
template <class Item>
void List<Item>::insert(const Item& it, int index) {
	Node* newNode = new Node(it, NULL);
	if (mySize == 0) {
		myFirst = newNode;
		myLast = newNode;
	} else {
		if (index <= 0) {
			newNode->myNext = myFirst;
			myFirst = newNode;
		} else if (index > (int)mySize) {
			myLast->myNext = newNode;
			myLast = newNode;
		} else {

			Node* current = myFirst;
			Node* next = current->myNext;

			for (int i = 0; i < index - 1; i++) {
				next = current->myNext;
				current = next;
			}

			newNode->myNext = next;
			current->myNext = newNode;
		}
	}

	mySize++;
}

/* remove
 * @param: int index, the index whose Node will be removed from the list
 * Return: Item, the item at that Node in the list
 * written by Ian Adams (isa3)
 */
template <class Item>
Item List<Item>::remove(int index) {
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

/*
 * Reads an arbitrary number of values from cin, appending each value to the list.
 * Terminates when '\n' is received from the stream.
 * written by Shion Fukuzawa (sf27)
 */
template <class Item>
void List<Item>::readFrom(istream& in) {
	Item newValue;

	string line;
	getline(in, line);
	istringstream iss(line);
	while (iss >> newValue)
		append(newValue);
}

/* writeTo
 * @param: ostream&, the stream being written to
 * Return: none
 * written by Ian Adams (isa3)
 */
template <class Item>
void List<Item>::writeTo(ostream& out) const {
	Node * myPtr = myFirst;
	while (myPtr != NULL) {
		out << myPtr->myItem << " " << flush;
		myPtr = myPtr->myNext;
	}
	out << '\n' << flush;
}

/* readFrom
 * @param: string&, the fileName being read from
 * Return: none
 * written by Ian Adams (isa3)
 */
template <class Item>
void List<Item>::readFrom(const string& fileName) {
	ifstream fin(fileName.c_str());
	assert(fin.is_open());
	readFrom(fin);
	fin.close();
}

/*
 * Writes all values stored in the list to a file separated by ' ' and ended with '\n'
 * written by Shion Fukuzawa
 */
template <class Item>
void List<Item>::writeTo(const string& fileName) {
	ofstream fout(fileName.c_str());
	assert( fout.is_open() );
	Node* current = myFirst;
	Node* next = NULL;

	while (current != NULL) {
		next = current->myNext;
		fout << current->myItem << ' ' << flush;
		current = next;
	}
	fout << '\n' << flush;

	fout.close();
}

#endif /* LIST_H_ */
