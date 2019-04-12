/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name:
 * Date:
 * 
 * Class Invariant: 
 *    mySize == 0 ||
 *    mySize > 0 && myArray[myFirst] == getFirst()
 *               && myArray[myLast-1] == getLast().
 * 
 *  (When I am not empty:
 *     myFirst is the index of my oldest value;
 *     myLast is the index of the spot where the next
 *       item to be appended will be placed.)      
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"
#include <cstring>

template <class Item>
class ArrayQueue {
public:

	ArrayQueue(int capacity);
	ArrayQueue(const ArrayQueue<Item>& original);
	virtual ~ArrayQueue();

	ArrayQueue<Item>& operator=(const ArrayQueue<Item>& original);

	unsigned getSize() const;
	unsigned getCapacity() const;
	Item getFirst() const;
	Item getLast() const;

	void setCapacity(unsigned newCapacity);

	bool isEmpty() const;
	bool isFull() const;

	void append(const Item newItem);
	Item remove();

protected:
	virtual void makeCopyOf(const ArrayQueue<Item>& original);
private:
	unsigned mySize;       // number of items I contain
	unsigned myCapacity;   // how many items I can store
	unsigned myFirst;      // index of oldest item (if any)
	unsigned myLast;       // index of next available spot for append (if any)
	Item*    myArray;      // dynamic array of items

	friend class ArrayQueueTester;
};

template <class Item>
ArrayQueue<Item>::ArrayQueue(int capacity) {
	if (capacity <= 0) {
		throw QueueException("Explicit constructor", "The capacity must be positive!");
	}
	mySize = 0;
	myCapacity = capacity;
	myFirst = 0;
	myLast = capacity - 1;
	myArray = new Item[myCapacity];
}

template <class Item>
ArrayQueue<Item>::ArrayQueue(const ArrayQueue& original) {
	makeCopyOf(original);
}

template <class Item>
void ArrayQueue<Item>::makeCopyOf(const ArrayQueue& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirst = original.myFirst;
	myLast = original.myLast;
	myArray = new Item[myCapacity];
	memcpy(myArray, original.myArray, myCapacity*sizeof(Item) );
}

template <class Item>
ArrayQueue<Item>::~ArrayQueue() {
	delete [] myArray;
	myArray = NULL;
	mySize = myFirst = myLast = 0;
}

template <class Item>
ArrayQueue<Item>& ArrayQueue<Item>::operator=(const ArrayQueue<Item>& aQueue) {
	if (this != &aQueue) {
		delete [] myArray;
		makeCopyOf(aQueue);
	}
	return *this;
}

template <class Item>
unsigned ArrayQueue<Item>::getCapacity() const {
	return myCapacity;
}

template <class Item>
unsigned ArrayQueue<Item>::getSize() const {
	return mySize;
}

template <class Item>
Item ArrayQueue<Item>::getFirst() const {
	if (isEmpty()) {
		throw EmptyQueueException("ArrayQueue::getFirst()");
	}
	return myArray[myFirst];
}

template <class Item>
Item ArrayQueue<Item>::getLast() const {
	if (isEmpty()) {
		throw EmptyQueueException("ArrayQueue::getLast()");
	}
	return myArray[myLast];
}

template <class Item>
void ArrayQueue<Item>::setCapacity(unsigned newCapacity) {
	if (newCapacity == 0 || newCapacity < getSize()) {
		throw QueueException("ArrayQueue::setCapacity()", "Capacity cannot be smaller than current size!");
		return;
	}
	Item* newArray = new Item[newCapacity];
	for (unsigned i = 0; i < mySize; i++) {
		newArray[i] = remove();
		mySize++;
	}
	delete [] myArray;
	myArray = newArray;
	myFirst = 0;
	myLast  = mySize - 1;
	myCapacity = newCapacity;
}


template <class Item>
bool ArrayQueue<Item>::isEmpty() const {
	return mySize == 0;
}

template <class Item>
bool ArrayQueue<Item>::isFull() const {
	return getSize() == myCapacity;
}

template <class Item>
void ArrayQueue<Item>::append(const Item newItem) {
	if (isFull()) {
		throw FullQueueException("ArrayQueue::append()");
	}
	myLast = (myLast + 1) % myCapacity;
	myArray[myLast] = newItem;
	mySize++;
}

template <class Item>
Item ArrayQueue<Item>::remove() {
	if (isEmpty()) {
		throw EmptyQueueException("ArrayQueue::remove()");
	}
	mySize--;
	Item item = myArray[myFirst];
	myFirst = (myFirst + 1) % myCapacity;
	return item;
}

#endif /*ARRAY_QUEUE_H_*/
