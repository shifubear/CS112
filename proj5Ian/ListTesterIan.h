/* ListTester.h declares the test-class for class List.
 * Joel Adams, for CS 112 at Calvin College.
 * Student: Ian Adams (isa3)
 */

#ifndef LISTTESTERIAN_H_
#define LISTTESTERIAN_H_

class ListTester {
public:
	void runTests();
	void testDefaultConstructor();
	void testNodeDefaultConstructor();
	void testNodeExplicitConstructor();
	void testAppend();
	void testDestructor();
	void testCopyConstructor();
	void testAssignment();
	void testEquality();
	void testInequality();
	void testGetIndexOf();
	void testReadFromStream();
	void testReadFromString();
	void testWriteToStream();
	void testRemove();
};

#endif /*LISTTESTERIAN_H_*/
