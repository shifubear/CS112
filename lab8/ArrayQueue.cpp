/* ArrayQueue.cpp defines the methods for class ArrayQueue.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name:
 * Date:
 */

#include "ArrayQueue.h"
#include <cstring>      // memcpy()
using namespace std;

ArrayQueue::ArrayQueue(int capacity) {
	if (capacity <= 0) {
		throw QueueException("Explicit constructor", "The capacity must be positive!");
	}
	mySize = 0;
	myCapacity = capacity;
	myFirst = 0;
	myLast = capacity - 1;
	myArray = new int[myCapacity];
}

ArrayQueue::ArrayQueue(const ArrayQueue& original) {
	makeCopyOf(original);
}

void ArrayQueue::makeCopyOf(const ArrayQueue& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirst = original.myFirst;
	myLast = original.myLast;
	myArray = new Item[myCapacity];
	memcpy(myArray, original.myArray, myCapacity*sizeof(Item) );
}

ArrayQueue::~ArrayQueue() {
	delete [] myArray;
	myArray = NULL;
	mySize = myFirst = myLast = 0;
}


ArrayQueue& ArrayQueue::operator=(const ArrayQueue& aQueue) {
	if (this != &aQueue) {
		delete [] myArray;
		makeCopyOf(aQueue);
	}
	return *this;
}

unsigned ArrayQueue::getCapacity() const {
	return myCapacity;
}

unsigned ArrayQueue::getSize() const {
	return mySize;
}

Item ArrayQueue::getFirst() const {
	if (isEmpty()) {
		throw EmptyQueueException("ArrayQueue::getFirst()");
	}
	return myArray[myFirst];
}

Item ArrayQueue::getLast() const {
	if (isEmpty()) {
		throw EmptyQueueException("ArrayQueue::getLast()");
	}
	return myArray[myLast];
}

bool ArrayQueue::isEmpty() const {
	return mySize == 0;
}

bool ArrayQueue::isFull() const {
	return getSize() == myCapacity;
}

void ArrayQueue::append(const Item newItem) {
	if (isFull()) {
		throw FullQueueException("ArrayQueue::append()");
	}
	myLast = (myLast + 1) % myCapacity;
	myArray[myLast] = newItem;
	mySize++;
}

Item ArrayQueue::remove() {
	if (isEmpty()) {
		throw EmptyQueueException("ArrayQueue::remove()");
	}
	mySize--;
	Item item = myArray[myFirst];
	myFirst = (myFirst + 1) % myCapacity;
	return item;

}





