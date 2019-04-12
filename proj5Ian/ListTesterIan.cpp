/* ListTester.cpp defines the test methods for class List.
 * Joel Adams, for CS 112 at Calvin College.
 */


#include "ListTesterIan.h" // ListTester

#include <iostream>     // cin, cout
#include <cassert>      // assert()
#include <cstdlib>      // exit()
#include <stdexcept>    // underflow_error

#include "ListIan.h"       // List
using namespace std;

void ListTester::runTests() {
	cout << "Running List tests..." << endl;
	testDefaultConstructor();
	testNodeDefaultConstructor();
	testNodeExplicitConstructor();
	testAppend();
	testDestructor();
	testCopyConstructor();
	testAssignment();
	testInequality();
	testReadFromStream();
	testReadFromString();
	testWriteToStream();
	testGetIndexOf();
	testRemove();
	cout << "All tests passed!" << endl;
}

void ListTester::testDefaultConstructor() {
	cout << "Testing List default constructor... " << flush;
	List aList;
	assert( aList.mySize == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeDefaultConstructor() {
	cout << "Testing Node default constructor... " << flush;
	List::Node aNode;
	assert( aNode.myItem == Item() );
	assert( aNode.myNext == NULL );
	cout << "Passed!" << endl;
}

void ListTester::testNodeExplicitConstructor() {
	cout << "Testing Node explicit constructor... " << flush;
	List::Node n1(11, NULL);
	assert( n1.myItem == 11 );
	assert( n1.myNext == NULL );
	cout << " 1 " << flush;

	List::Node *n3 = new List::Node(33, NULL);
	List::Node n2(22, n3);
	assert( n2.myItem == 22 );
	assert( n2.myNext == n3 );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAppend() {
	cout << "Testing append()... " << flush;
	// empty List
	List aList;
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	try {
		aList.getFirst();
		cerr << "getFirst() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0a " << flush;
	}
	try {
		aList.getLast();
		cerr << "getLast() worked on empty list" << endl;
		exit(1);
	} catch (underflow_error&) {
		cout << " 0b " << flush;
	}
	// append to empty list
	aList.append(11);
	assert( aList.getSize() == 1 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast == aList.myFirst );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 11 );
	assert( aList.myFirst->myNext == NULL );
	cout << " 1 " << flush;
	// append to a list containing 1 Item
	aList.append(22);
	assert( aList.getSize() == 2 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.myFirst != aList.myLast );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 22 );
	assert( aList.myFirst->myNext != NULL );
	assert( aList.myLast->myNext == NULL );
	cout << " 2 " << flush;
	// append to a list containing 2 Items
	aList.append(33);
	assert( aList.getSize() == 3 );
	assert( aList.myFirst != NULL );
	assert( aList.myLast != NULL );
	assert( aList.getFirst() == 11 );
	assert( aList.getLast() == 33 );
	assert( aList.myFirst->myNext->myItem == 22 );
	assert( aList.myLast->myNext == NULL );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testDestructor() {
	cout << "Testing destructor... " << flush;
	List aList;
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 1 " << flush;

	aList.append(11);
	aList.append(22);
	aList.append(33);
	aList.~List();
	assert( aList.getSize() == 0 );
	assert( aList.myFirst == NULL );
	assert( aList.myLast == NULL );
	cout << " 2 " << flush;
	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testCopyConstructor() {
	cout << "Testing copy constructor... " << flush;
	// copy empty list
	List list1;
	List list2(list1);
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// copy nonempty list
	List list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List list4(list3);
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;
	cout << "Passed!" << endl;
}

void ListTester::testAssignment() {
	cout << "Testing assignment... " << flush;
	// empty to empty assignment
	List list1;
	List list2;
	list2 = list1;
	assert( list2.getSize() == 0 );
	assert( list2.myFirst == NULL );
	assert( list2.myLast == NULL );
	cout << " 1 " << flush;

	// non-empty to empty assignment
	List list3;
	list3.append(11);
	list3.append(22);
	list3.append(33);
	List list4;
	list4 = list3;
	assert( list4.getSize() == 3 );
	assert( list4.getFirst() == 11 );
	assert( list4.getLast() == 33 );
	assert( list4.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list4.myFirst != list3.myFirst );
	assert( list4.myFirst->myNext != list3.myFirst->myNext );
	assert( list4.myLast != list3.myLast );
	cout << " 2 " << flush;

	// equal-sized non-empty to non-empty assignment
	List list5;
	list5.append(44);
	list5.append(55);
	list5.append(66);
	list5 = list3;
	assert( list5.getSize() == 3 );
	assert( list5.getFirst() == 11 );
	assert( list5.getLast() == 33 );
	assert( list5.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list5.myFirst != list3.myFirst );
	assert( list5.myFirst->myNext != list3.myFirst->myNext );
	assert( list5.myLast != list3.myLast );
	cout << " 3 " << flush;

	// empty to non-empty assignment
	List list6;
	list6.append(44);
	list6.append(55);
	list6.append(66);
	List list7;
	list6 = list7;
	assert( list6.getSize() == 0 );
	assert( list6.myFirst == NULL );
	assert( list6.myLast == NULL );
	cout << " 4 " << flush;

	// unequal-sized non-empty to non-empty assignment
	List list8;
	list8.append(44);
	list8.append(55);
	list8.append(66);
	list8.append(77);
	list8 = list3;
	assert( list8.getSize() == 3 );
	assert( list8.getFirst() == 11 );
	assert( list8.getLast() == 33 );
	assert( list8.myFirst->myNext->myItem == 22 );
      // check that nodes are distinct
	assert( list8.myFirst != list3.myFirst );
	assert( list8.myFirst->myNext != list3.myFirst->myNext );
	assert( list8.myLast != list3.myLast );
	cout << " 5 " << flush;

	// assignment chaining
	List list9;
	list9.append(44);
	list9.append(55);
	list9.append(66);
	list9.append(77);
	List list10;
	list10 = list9 = list8;
	assert( list10.getSize() == 3 );
	assert( list10.getFirst() == 11 );
	assert( list10.getLast() == 33 );
	assert( list10.myFirst->myNext->myItem == 22 );
	cout << " 6 " << flush;

	// self-assignment (stupid, but possible)
	List list11;
	list11.append(11);
	list11.append(22);
	list11.append(33);
	list11 = list11;
	assert( list11.getSize() == 3 );
	assert( list11.getFirst() == 11 );
	assert( list11.getLast() == 33 );
	assert( list11.myFirst->myNext->myItem == 22 );
	cout << " 7 " << flush;

	cout << "Passed!  But double-check for memory leaks!" << endl;
}

void ListTester::testInequality() {
	cout << "Testing inequality..." << flush;
	//empty/empty
	List list1;
	List list2;
	assert( (list1 != list2) == false);
	cout << " 0 " << flush;
	//empty/non-empty
	List list3;
	list3.append(2);
	list3.append(4);
	list3.append(8);
	assert( (list1 != list3) == true);
	cout << " 1 " << flush;
	//non-empty/non-empty, same list
	List list4;
	list4.append(2);
	list4.append(4);
	list4.append(8);
	assert( (list3 != list4) == false);
	cout << " 2 " << flush;
	//non-empty/non-empty, different lists
	List list5;
	list5.append(3);
	list5.append(6);
	list5.append(9);
	assert( (list3 != list5) == true);
	cout << " 3 " << flush;
	//different size lists
	List list6;
	list6.append(2);
	list6.append(4);
	list6.append(8);
	list6.append(16);
	assert( (list3 != list6) == true);
	cout << " 4 " << flush;

	cout << "Passed! " << endl;
}

void ListTester::testGetIndexOf() {
	cout << "Testing getIndexOf()... " << flush;
	//non-empty
	List list1;
	list1.append(5);
	list1.append(15);
	list1.append(30);
	list1.append(25);
	assert(list1.getIndexOf(5) == 0);
	assert(list1.getIndexOf(15) == 1);
	assert(list1.getIndexOf(30) == 2);
	assert(list1.getIndexOf(25) == 3);
	assert(list1.getIndexOf(40) == -1);
	cout << " 0 " << flush;
	//empty
	List list2;
	assert( list2.getIndexOf(1) == -1);
	cout << " 1 " << flush;

	cout << "Passed!" << endl;
}

void ListTester::testRemove() {
	cout << "Testing remove()... " << flush;
	List list1;
	list1.append(1);
	list1.append(5);
	list1.append(8);
	list1.append(13);
	list1.append(21);
	//middle index
	Item it1 = list1.remove(2);
	assert(list1.mySize == 4);
	assert(list1.myFirst->myNext->myItem == 5);
	assert(list1.myFirst->myNext->myNext->myItem == 13);
	assert(it1 == 8);
	cout << " 0 " << flush;
	//beginning index
	Item it2 = list1.remove(-1);
	assert(list1.mySize == 3);
	assert(list1.myFirst->myItem == 5);
	assert(it2 == 1);
	cout << " 1 " << flush;
	//ending index
	Item it3 = list1.remove(10);
	assert(list1.mySize == 2);
	assert(list1.myLast->myItem == 13);
	assert(it3 == 21);
	cout << " 2 " << flush;
	List list2;
	try {
		list2.remove(5);
		cerr << "remove() worked on an empty list" << endl;
	} catch (range_error&) {
		cout << " 3 " << flush;
	}

	cout << "Passed! But double check for memory leaks!" << endl;
}

void ListTester::testWriteToStream() {
	cout << "Testing writeTo(ostream)... " << flush;
	List list1;
	list1.readFrom("ListTest1.txt");
	ofstream fout("ListTest1Copy.txt");
	assert( fout.is_open());
	list1.writeTo(fout);
	fout.close();

	cout << "Passed!" << endl;
}

void ListTester::testReadFromString() {
	cout << "Testing readFrom(string)... " << flush;
	List list1;
	list1.readFrom("ListTest1.txt");
	assert(list1.mySize == 3);
	assert( list1.myFirst->myItem == 4);
	assert( list1.myFirst->myNext->myItem == 8);
	assert( list1.myFirst->myNext->myNext->myItem == 16);
	cout << "Passed!" << endl;
}

void ListTester::testReadFromStream() {
	cout << "Testing readFrom(istream)... " << flush;
	//non-empty file
	List list1;
	ifstream fin("ListTest1.txt");
	assert(fin.is_open());
	list1.readFrom(fin);
	assert(list1.mySize == 3);
	assert( list1.myFirst->myItem == 4);
	assert( list1.myFirst->myNext->myItem == 8);
	assert( list1.myFirst->myNext->myNext->myItem == 16);
	fin.close();

	cout << "Passed!" << endl;
}

