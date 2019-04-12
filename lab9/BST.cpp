/* BST.cpp defines binary search tree methods.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name:
 * Date:
 */
 
#include "BST.h"

BST::BST() {
	myRoot = NULL;
	myNumItems = 0;
}

BST::~BST() {
	delete myRoot;
	myRoot = NULL;
	myNumItems = 0;
}

BST::Node::Node(const Item& it) {
   myItem = it;
   myLeft = NULL;
   myRight = NULL;
}

BST::Node::~Node() {
	delete myLeft;
	delete myRight;
}

bool BST::isEmpty() const {
	return myNumItems == 0;
}

unsigned BST::getNumItems() const {
	return myNumItems;
}

void BST::insert(const Item& it) {
	Node* newNode = new Node(it);
	if (myRoot == NULL) {
		myRoot = newNode;
	} else {
		try {
			myRoot->insert(it);
		} catch (Exception& ex) {
			throw ex;
		}
	}

	myNumItems++;
}

void BST::Node::insert(const Item& it) {
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

bool BST::contains(const Item& it) {
	if (myRoot == NULL)
		return false;

	if (myRoot->myItem == it) {
		return true;
	} else {
		return myRoot->contains(it);
	}
}

bool BST::Node::contains(const Item& it) {

	if (myItem == it) {
		return true;
	} else {
		return (myLeft  != NULL && myLeft->contains(it)) ||
			   (myRight != NULL && myRight->contains(it));
	}
}

void BST::Node::processItem() {
	cout << ' ' << myItem;
}

void BST::traversePreorder() {
	if ( !isEmpty() ) {
		myRoot->traversePreorder();
	}
}

void BST::Node::traversePreorder() {
	processItem();
	if (myLeft != NULL) {
		myLeft->traversePreorder();
	}
	if (myRight != NULL) {
		myRight->traversePreorder();
	}
}

void BST::traversePostorder() {
	if ( !isEmpty() ) {
		myRoot->traversePostorder();
	}
}

void BST::Node::traversePostorder() {
	if (myLeft != NULL) {
		myLeft->traversePostorder();
	}
	if (myRight != NULL) {
		myRight->traversePostorder();
	}
	processItem();
}

void BST::traverseInorder() {
	if ( !isEmpty() ) {
		myRoot->traverseInorder();
	}
}

void BST::Node::traverseInorder() {
	if (myLeft != NULL) {
		myLeft->traverseInorder();
	}
	processItem();
	if (myRight != NULL) {
		myRight->traverseInorder();
	}
}






