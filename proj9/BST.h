/* BST.h declares a "classic" binary search tree of linked nodes.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 * 
 * Class Invariant:
 *   myNumItems == 0 && myRoot == NULL ||
 *   myNumItems > 0 && 
 *     myRoot stores the address of a Node containing an item &&
 *       all items in myRoot->myLeft are less than myRoot->myItem &&
 *       all items in myRoot->myRight are greater than myRoot->myItem.
 */

#ifndef BST_H_
#define BST_H_

#include "Exception.h"
#include "ArrayQueue.h"

#include <iostream>
using namespace std;

typedef int Item;

template <class Item>
class BST {
public:

	BST();
	virtual ~BST();
	bool isEmpty() const;
	unsigned getNumItems() const;

	void insert(const Item& it);
	bool contains(const Item& it);
	unsigned getHeight() const;

	void traverseInorder();
	void traversePreorder();
	void traversePostorder();

private:
	struct Node {
	    Node(const Item& it);
            virtual ~Node();

            void insert(const Item& it);
            bool contains(const Item& it);

            void traverseInorder();
            void traversePreorder();
            void traversePostorder();
            virtual void processItem();
		
            Item myItem;
            Node* myLeft;
            Node* myRight;
	};
	
	Node* myRoot;
	unsigned myNumItems;
	friend class BST_Tester;
};

/*
 * Default constructor. Initializes all default values.
 */
template <class Item>
BST<Item>::BST() {
	myRoot = NULL;
	myNumItems = 0;
}

/*
 * Destructor
 */
template <class Item>
BST<Item>::~BST() {
	delete myRoot;
	myRoot = NULL;
	myNumItems = 0;
}

/*
 * Node constructor. Takes item as parameter.
 */
template <class Item>
BST<Item>::Node::Node(const Item& it) {
   myItem = it;
   myLeft = NULL;
   myRight = NULL;
}

/*
 * Node destructor. Recursive destruction.
 */
template <class Item>
BST<Item>::Node::~Node() {
	delete myLeft;
	delete myRight;
}

/*
 * Checks if BST is empty or not.
 */
template <class Item>
bool BST<Item>::isEmpty() const {
	return myNumItems == 0;
}

/*
 * Returns number of items in BST
 */
template <class Item>
unsigned BST<Item>::getNumItems() const {
	return myNumItems;
}

/*
 * Inserts an item into the BST recursively.
 *
 */
template <class Item>
void BST<Item>::insert(const Item& it) {
	Node* newNode = new Node(it);
	if (myRoot == NULL) {
		myRoot = newNode;
	} else {
		try {
			myRoot->insert(it);
		} catch (Exception& ex) {
			throw Exception("insert", "Cannot insert Node with existing value!");
		}
	}

	myNumItems++;
}

/*
 * Recursive insert method.
 *
 * Throws an error if a node with an existing value is found.
 *
 */
template <class Item>
void BST<Item>::Node::insert(const Item& it) {
	Node* newNode = new Node(it);
	if (it < myItem) {
		if (myLeft == NULL)
			myLeft  = newNode;
		else
			myLeft->insert(it);
	} else if (it > myItem) {
		if (myRight == NULL)
			myRight = newNode;
		else
			myRight->insert(it);
	} else {
		throw Exception("Node insert", "Cannot insert Node with existing value");
	}
}

/*
 * Checks if Item it exists in the BST recursively.
 */
template <class Item>
bool BST<Item>::contains(const Item& it) {
	if (myRoot == NULL)
		return false;

	if (myRoot->myItem == it) {
		return true;
	} else {
		return myRoot->contains(it);
	}
}

/*
 * Recursive node method to find if the BST contains item.
 */
template <class Item>
bool BST<Item>::Node::contains(const Item& it) {

	if (myItem == it) {
		return true;
	} else {
		return (myLeft  != NULL && myLeft->contains(it)) ||
			   (myRight != NULL && myRight->contains(it));
	}
}

/*
 * Returns the height of the BST.
 */
template <class Item>
unsigned BST<Item>::getHeight() const {
	unsigned height = 0;
	ArrayQueue<Node *> myQueue(1);

	if (myRoot != NULL)
		myQueue.append(myRoot);


	while (!myQueue.isEmpty()) {

		int queueSize = myQueue.getSize();

		for (int i = 0; i < queueSize; i++) {
			Node* currentNode = myQueue.remove();
			if (currentNode->myLeft != NULL) {
				try {
					myQueue.append(currentNode->myLeft);
				} catch (QueueException& qe) {
					myQueue.setCapacity( myQueue.getCapacity() * 2 );
					myQueue.append(currentNode->myLeft);
				}
			}
			if (currentNode->myRight != NULL) {
				try {
					myQueue.append(currentNode->myRight);
				} catch (QueueException& qe) {
					myQueue.setCapacity( myQueue.getCapacity() * 2 );
					myQueue.append(currentNode->myRight);
				}
			}
		}

		height++;
	}


	return height;

}

template <class Item>
void BST<Item>::Node::processItem() {
	cout << ' ' << myItem;
}

template <class Item>
void BST<Item>::traversePreorder() {
	if ( !isEmpty() ) {
		myRoot->traversePreorder();
	}
}

template <class Item>
void BST<Item>::Node::traversePreorder() {
	processItem();
	if (myLeft != NULL) {
		myLeft->traversePreorder();
	}
	if (myRight != NULL) {
		myRight->traversePreorder();
	}
}

template <class Item>
void BST<Item>::traversePostorder() {
	if ( !isEmpty() ) {
		myRoot->traversePostorder();
	}
}

template <class Item>
void BST<Item>::Node::traversePostorder() {
	if (myLeft != NULL) {
		myLeft->traversePostorder();
	}
	if (myRight != NULL) {
		myRight->traversePostorder();
	}
	processItem();
}

template <class Item>
void BST<Item>::traverseInorder() {
	if ( !isEmpty() ) {
		myRoot->traverseInorder();
	}
}

template <class Item>
void BST<Item>::Node::traverseInorder() {
	if (myLeft != NULL) {
		myLeft->traverseInorder();
	}
	processItem();
	if (myRight != NULL) {
		myRight->traverseInorder();
	}
}

#endif /*BST_H_*/

