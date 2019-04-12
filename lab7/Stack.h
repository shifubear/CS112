/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 * 
 * Invariant: mySize == 0 && isEmpty() && !isFull()
 *         || mySize == myCapacity && !isEmpty() && isFull()
 *         || mySize > 0 && mySize < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member mySize always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack::Overflow.
 * 3. Sending pop() or peekTop() to an empty Stack throws the exception Stack::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

#include "StackException.h"
#include <string>
#include <iostream>
using namespace std;


template <class Item>
class Stack {
public:
	Stack(unsigned capacity);
	Stack(const Stack<Item>& original);
	~Stack();

	unsigned getSize() const { return mySize; }
	unsigned getCapacity() const { return myCapacity; }
	void setCapacity(unsigned capacity);

	Stack<Item>& operator=(const Stack<Item>& original);
	
	bool isEmpty() const;
	bool isFull()  const;
	Item peekTop() const;
	void push(const Item& item);
	Item pop();

protected:
	void makeCopyOf(const Stack<Item>& original);
	
private:
	unsigned myCapacity;
	unsigned mySize;
	Item*    myArray;
	friend class StackTester;
};

/* explicit-value constructor
 * Parameter: capacity, an unsigned value.
 * Precondition: capacity > 0.
 * Postcondition: mySize == 0 && myCapacity == capacity
 *              && myArray contains the address of a dynamic array of 'capacity' entries.
 */
template <class Item>
Stack<Item>::Stack(unsigned capacity) {
	if (capacity <= 0) {
		throw StackException("Stack(size)", "size must be positive!");
	} else {
		mySize = 0;
		myCapacity = capacity;
		myArray = new Item[capacity];
	}
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template <class Item>
Stack<Item>::Stack(const Stack<Item>& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
template <class Item>
void Stack<Item>::makeCopyOf(const Stack<Item>& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	mySize = original.mySize;
}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
template <class Item>
Stack<Item>::~Stack() {
	delete [] myArray;
	myArray = NULL;
	myCapacity = 0;
	mySize = 0;
}

/*
 * @param: capacity, the desired new capacity.
 * Postcondition: Sets myCapacity to capacity and copies all values inside. If the new capacity is
 * smaller than mySize, throws an exception.
 */
template <class Item>
void Stack<Item>::setCapacity(unsigned capacity) {
	if (capacity < mySize) {
		throw StackException("setCapacity()", "cannot set capacity to be lower than current size.");
	} else {
		Item* newArray = new Item[capacity];
		for (unsigned i = 0; i < myCapacity; i++) {
			newArray[i] = myArray[i];
		}
		delete [] myArray;
		myArray = newArray;
		myCapacity = capacity;
	}
}


/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
template <class Item>
Stack<Item>& Stack<Item>::operator=(const Stack<Item>& original) {
	if (this != &original) {
		delete [] myArray;
		makeCopyOf(original);
	}
	return *this;
}

/*
 * Returns true if the stack is empty.
 */
template <class Item>
bool Stack<Item>::isEmpty() const {
	return mySize == 0;
}

/*
 * Returns true if the stack is full.
 */
template <class Item>
bool Stack<Item>::isFull() const {
	return mySize == myCapacity;
}

/*
 * Returns the value of the item on the top of the stack.
 */
template <class Item>
Item Stack<Item>::peekTop() const {
	if ( isEmpty() ) {
		throw StackException("peekTop()", "stack is empty");
	} else {
		return myArray[mySize - 1];
	}
}


/*
 * Pushes the item given onto the top of the stack
 */
template <class Item>
void Stack<Item>::push(const Item& item) {
	if ( isFull() ) {
		throw StackException("push()", "stack is full!");
	} else {
		myArray[mySize++] = item;
	}
}

/*
 * Removes the top item of the stack and returns it.
 */
template <class Item>
Item Stack<Item>::pop() {
	if ( isEmpty() ) {
		throw StackException("pop()", "stack is empty!");
	} else {
		return myArray[(mySize--) - 1];
	}
}


#endif

