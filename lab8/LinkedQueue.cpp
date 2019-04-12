/* LinkedQueue.cpp defines the methods for class LinkedQueue.
 * Joel Adams, for CS 112 at Calvin College.
 * Student name:
 * Date:
 */

#include "LinkedQueue.h"

LinkedQueue::LinkedQueue() {
	mySize = 0;
	myFirst = NULL;
	myLast  = NULL;
}

LinkedQueue::LinkedQueue(const LinkedQueue& original) {
	makeCopyOf(original);
}

void LinkedQueue::makeCopyOf(const LinkedQueue& original) {
	mySize = original.mySize;
	if ( mySize == 0 ) {
		myFirst = myLast = NULL;
	} else {
		myFirst = new Node(original.getFirst(), NULL);
		Node * temp0 = original.myFirst->myNext;
		Node * temp1 = myFirst;
		while (temp0 != NULL) {
			temp1->myNext = new Node(temp0->myItem, NULL);
			temp1 = temp1->myNext;
			temp0 = temp0->myNext;
		}
		myLast = temp1;
	}
}

LinkedQueue::~LinkedQueue() {
	delete myFirst;
	myFirst = myLast = NULL;
	mySize = 0;
}

LinkedQueue& LinkedQueue::operator=(const LinkedQueue& aQueue) {
	if (this != &aQueue) {
		delete myFirst;    // invokes recursive ~Node()
		makeCopyOf(aQueue);
	}
	return *this;
}

Item LinkedQueue::getFirst() const {
	if (isEmpty()) {
		throw EmptyQueueException("LinkedQueue::getFirst()");
	}
	return myFirst->myItem;
}

Item LinkedQueue::getLast() const {
	if (isEmpty()) {
		throw EmptyQueueException("LinkedQueue::getLast()");
	}
	return myLast->myItem;
}

void LinkedQueue::append(const Item newItem) {
	if (isFull()) {
		throw FullQueueException("LinkedQueue::append");
	}
	Node* newNode = new Node(newItem, NULL);
	if (isEmpty()) {
		myFirst = newNode;
	} else {
		myLast->myNext = newNode;
	}
	myLast = newNode;
	mySize++;
}

Item LinkedQueue::remove() {
	if (isEmpty()) {
		throw EmptyQueueException("LinkedQueue::remove");
	}
	Item result = myFirst->myItem;
	Node* temp = myFirst;
	myFirst = myFirst->myNext;
	temp->myNext = NULL;
	delete temp;
	mySize--;
	return result;
}

