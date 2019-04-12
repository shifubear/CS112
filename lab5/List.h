/* List.h provides a class for storing information using a Linked List structure.
 * List.h
 * Student Name: Shion Fukuzawa
 * Date: February 28, 2017
 */

#ifndef LIST_H_
#define LIST_H_

typedef double Item;

class List {
public:
	List();
	List(const List& original);
	virtual ~List();

	unsigned getSize() const { return mySize; }
	Item getFirst() const;
	Item getLast() const;

	List& operator=(const List& original);

	void append(const Item& it);

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

	void makeCopyOf(const List& original);

	friend class ListTester;
};

#endif /* LIST_H_ */
