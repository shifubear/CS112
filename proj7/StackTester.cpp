/* StackTester.cpp defines test-methods for the 
 *  dynamically allocated (array) Stack operations
 * Joel Adams, for CS 112 at Calvin College
 */

#include "StackTester.h"
#include "Stack.h"
#include <iostream>  // cout, cerr, ...
#include <cassert>   // assert()
#include <cstdlib>   // exit()
using namespace std;

void StackTester::runTests() {
	cout << "Testing Stack class..." << endl;
	testConstructor();
	testIsEmpty();
	testPushPeekTopAndIsFull();
	testPop();
	testCopyConstructor();
	testAssignment();
	testDestructor();
	testGetSize();
	testGetCapacity();
	testSetCapacity();
	cout << "All tests passed!" << endl;
}

void StackTester::testConstructor() {
	cout << "- Testing constructor... " << flush;
	// invalid parameter
	try {
		Stack<double> s1(0);
		cerr << "\nConstructed stack of size 0\n";
		exit(1);
	} catch (StackException& se) {
		cout << se << flush;
	}
	cout << " 1 " << flush;
	// valid parameter
	Stack<double> s2(3);
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testIsEmpty() {
	cout << "- Testing isEmpty()... " << flush;
	// capacity 1
	Stack<double> s1(1);
	assert( s1.isEmpty() );
	cout << " 1 " << flush;
	// capacity > 1
	Stack<double> s2(3);
	assert( s2.isEmpty() );
	cout << " 2 " << flush;
	cout << " Passed!" << endl;
}


void StackTester::testPushPeekTopAndIsFull() {
	cout << "- Testing push()... " << flush;
	// test with capacity 1
	Stack<double> s1(1);
	s1.push(11);
	assert( s1.peekTop() == 11 );
	assert( !s1.isEmpty() );
	assert( s1.isFull() );
	try {
		s1.push(22);
		cerr << "\npush() worked on a full stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 1 " << flush;
	}
	// test with capacity > 1
	Stack<double> s2(3);
	s2.push(11);
	assert( s2.peekTop() == 11 );
	s2.push(22);
	assert( s2.peekTop() == 22 );
	s2.push(33);
	assert( s2.peekTop() == 33 );
	try {
		s2.push(44);
		cerr << "\npush() worked on a full stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 2 " << flush;
	}
	cout << " Passed! " << endl;
}

void StackTester::testPop() {
	cout << "- Testing pop()... " << flush;
	// try empty, capacity 1
	Stack<double> s1(1);
	assert( s1.isEmpty() );
	try {
		s1.peekTop();
		cerr << "\npeekTop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 0a " << flush;
	}
	try {
		s1.pop();
		cerr << "\npop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 0b " << flush;
	}

	// try empty, capacity > 1
	Stack<double> s2(3);
	try {
		s2.pop();
		cerr << "\npop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 1a " << flush;
	}
	try {
		s2.peekTop();
		cerr << "\npeekTop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 1b " << flush;
	}

	// try non-empty, capacity 1
	Stack<double> s3(1);
	s3.push(11);
	assert( s3.peekTop() == 11 );
	assert( s3.pop() == 11 );
	cout << " 2 " << flush;
	try {
		s3.pop();
		cerr << "\ns3.pop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 2a " << flush;
	}
	try {
		s3.peekTop();
		cerr << "\ns3.peekTop() worked on empty stack (size 1)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 2b " << flush;
	}

	// try non-empty, capacity > 1
	Stack<double> s4(3);
	s4.push(11);
	s4.push(22);
	s4.push(33);
	assert( s4.peekTop() == 33 );
	assert( s4.pop() == 33 );
	assert( s4.peekTop() == 22 );
	assert( s4.pop() == 22 );
	assert( s4.peekTop() == 11 );
	assert( s4.pop() == 11 );
	cout << " 3 " << flush;
	try {
		s4.pop();
		cerr << "\ns4.pop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 3a " << flush;
	}
	try {
		s4.peekTop();
		cerr << "\ns4.peekTop() worked on empty stack (size 3)\n";
		exit(1);
	} catch (StackException& se) {
		cout << " 3b " << flush;
	}

	cout << " Passed!" << endl;
}

void StackTester::testCopyConstructor() {
	cout << "- Testing copy constructor... " << flush;
	// minimal empty Stack
	Stack<double> s1(1);
	Stack<double> s2(s1);
	assert( s2.isEmpty() );
	assert( s2.myArray != NULL );
	assert( s2.myCapacity == 1 );
	assert( s2.myArray != s1.myArray );
	cout << " 1 " << flush;
	// minimal non-empty Stack
	Stack<double> s3(1);
	s3.push(11);
	Stack<double> s4(s3);
	assert( !s4.isEmpty() );
	assert( s4.isFull() );
	assert( s4.peekTop() == 11 );
	assert( s4.myArray != s3.myArray );
	cout << " 2 " << flush;
	// non-minimal, non-empty stack
	Stack<double> s5(3);
	s5.push(11);
	s5.push(22);
	s5.push(33);
	Stack<double> s6(s5);
	assert( s6.myCapacity == s5.myCapacity );
	assert( s6.mySize == s5.mySize );
	assert( s6.myArray != s5.myArray );
	assert( s6.pop() == 33 );
	assert( s6.pop() == 22 );
	assert( s6.pop() == 11 );
	assert( s5.peekTop() == 33 );
	cout << " 3 " << flush;
	cout << "Passed!" << endl;
}

void StackTester::testAssignment() {
	cout << "- Testing assignment... " << flush;
	// minimal empty Stacks, same size
	Stack<double> s1(1);
	Stack<double> s2(1);
	s2 = s1;
	assert( s2.isEmpty() );
	assert( s2.myArray != NULL );
	assert( s2.myArray != s1.myArray );
	assert( s2.myCapacity == 1 );
	cout << " 1 " << flush;
	// minimal non-empty Stack to empty Stack, same capacity
	Stack<double> s3(1);
	s3.push(11);
	Stack<double> s4(1);
	s4 = s3;
	assert( !s4.isEmpty() );
	assert( s4.isFull() );
	assert( s4.peekTop() == 11 );
	assert( s4.myArray != s3.myArray );
	cout << " 2 " << flush;
	// minimal empty stack to non-empty stack, same capacity
	Stack<double> s5(1);
	Stack<double> s6(1);
	s6.push(11);
	s6 = s5;
	assert( s6.isEmpty() );
	assert( s6.myArray != NULL );
	assert( s6.myArray != s5.myArray );
	assert( s6.myCapacity == 1 );
	cout << " 3 " << flush;
	// non-minimal non-empty stack to empty stack, different capacities
	Stack<double> s7(3);
	s7.push(11);
	s7.push(22);
	s7.push(33);
	Stack<double> s8(2);
	s8 = s7;
	assert( s8.myArray != s7.myArray );
	assert( s8.myCapacity == s7.myCapacity );
	assert( s8.mySize == s7.mySize );
	assert( s8.pop() == 33 );
	assert( s8.pop() == 22 );
	assert( s8.pop() == 11 );
	assert( s7.peekTop() == 33 );
	cout << " 4 " << flush;
	// non-minimal, empty stack to non-empty stack, different capacities
	Stack<double> s9(2);
	Stack<double> s10(3);
	s10.push(11);
	s10.push(22);
	s10.push(33);
	s10 = s9;
	assert( s10.isEmpty() );
	assert( s10.myArray != s9.myArray );
	assert( s10.myCapacity == s10.myCapacity );
	cout << " 5 " << flush;
	// self-assignment, minimal size
	Stack<double> s11(1);
	s11.push(11);
	s11 = s11;
	assert( s11.isFull() );
	assert( !s11.isEmpty() );
	cout << " 6 " << flush;
	// chaining
	Stack<double> s12(2);
	s12.push(11);
	s12.push(22);
	Stack<double> s13(1);
	Stack<double> s14(1);
	s14 = s13 = s12;
	assert( s14.isFull() );
	assert( s14.myArray != s13.myArray );
	assert( s14.myArray != s12.myArray );
	assert( s14.pop() == 22 );
	assert( s14.pop() == 11 );
	assert( s14.isEmpty() );
	cout << " 7 " << flush;
      // self-assignment, non-minimal size
      s13 = s13;
	assert( !s13.isEmpty() );
	assert( s13.isFull() );
	assert( s13.pop() == 22 );
	assert( s13.pop() == 11 );
	assert( s13.isEmpty() );
	cout << " 8 " << flush;
	cout << "Passed!" << endl;
}

void StackTester::testDestructor() {
	cout << "- Testing destructor..." << flush;
	// minimal, empty
	Stack<double> s1(1);
	s1.~Stack();
	assert( s1.isEmpty() );
	assert( s1.myArray == NULL );
	assert( s1.myCapacity == 0 );
	cout << " 1 " << flush;
	// minimal, non-empty
	Stack<double> s2(1);
	s2.push(11);
	s2.~Stack();
	assert( s2.isEmpty() );
	assert( s2.myArray == NULL );
	assert( s2.myCapacity == 0 );
	cout << " 2 " << flush;
	// non-minimal, empty
	Stack<double> s3(3);
	s3.~Stack();
	assert( s3.isEmpty() );
	assert( s3.myArray == NULL );
	assert( s3.myCapacity == 0 );
	cout << " 3 " << flush;
	// non-minimal, non-empty
	Stack<double> s4(3);
	s4.push(11);
	s4.push(22);
	s4.push(33);
	s4.~Stack();
	assert( s4.isEmpty() );
	assert( s4.myArray == NULL );
	assert( s4.myCapacity == 0 );
	cout << " 4 " << flush;
	cout << " Passed!" << endl;
}

void StackTester::testGetSize() {
	cout << "- Testing getSize()... " << flush;

	// Empty stack
	Stack<double> s0(5);
	assert( s0.getSize() == 0 );
	cout << " 0 " << flush;

	// 1 Item
	s0.push(1);
	assert( s0.getSize() == 1 );
	cout << " 1 " << flush;

	// Full stack
	s0.push(2);
	s0.push(3);
	s0.push(4);
	s0.push(5);
	assert( s0.getSize() == 5 );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;
}

void StackTester::testGetCapacity() {
	cout << "- Testing getCapacity()... " << flush;

	// Size 1 capacity
	Stack<double> s0(1);
	assert( s0.getCapacity() == 1 );
	cout << " 0 " << flush;

	// Size 1000 capacity
	Stack<double> s1(1000);
	assert( s1.getCapacity() == 1000 );
	cout << " 1 " << flush;

	// Pushes should not affect capacity
	Stack<double> s2(10);
	assert( s2.getCapacity() == 10 );
	cout << " 2 " << flush;
	s2.push(5);
	s2.push(10);
	assert( s2.getCapacity() == 10 );
	cout << " 3 " << flush;

	cout << " Passed!" << endl;
}

void StackTester::testSetCapacity() {
	cout << "- Testing setCapacity()... " << flush;

	// Increase capacity, empty stack
	Stack<double> s0(1);
	assert( s0.getCapacity() == 1 );
	assert( s0.getSize() == 0 );
	s0.setCapacity(5);
	assert( s0.getCapacity() == 5 );
	assert( s0.getSize() == 0 );
	cout << " 0 " << flush;

	// Decrease capacity, empty stack
	Stack<double> s1(5);
	assert( s1.getCapacity() == 5 );
	assert( s1.getSize() == 0 );
	s1.setCapacity(1);
	assert( s1.getCapacity() == 1 );
	assert( s1.getSize() == 0 );
	cout << " 1 " << flush;

	// Increase capacity, full stack
	Stack<double> s2(3);
	for (int i = 0; i < 3; i++) {
		s2.push(i + 1);
	}
	assert( s2.getCapacity() == 3 );
	assert( s2.getSize() == 3 );
	s2.setCapacity(5);
	assert( s2.getCapacity() == 5 );
	assert( s2.getSize() == 3 );
	cout << " 2 " << flush;

	// Decrease capacity, full stack, should throw exception
	Stack<double> s3(5);
	for (int i = 0; i < 5; i++) {
		s3.push(i + 1);
	}
	try {
		s3.setCapacity(3);
		cerr << "\nSet the capacity to be lower than the current size.\n" << flush;;
		exit(1);
	} catch (StackException& se) {
		cout << " 3 " << flush;
	}

//	try {
//		Stack<double> s1(0);
//		cerr << "\nConstructed stack of size 0\n";
//		exit(1);
//	} catch (StackException& se) {
//		cout << se << flush;
//	}
	cout << " Passed!" << endl;
}


