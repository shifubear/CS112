/* ListTester.h declares the test-class for class List.
 * Started by Joel Adams
 * Student Name: Shion Fukuzawa (sf27), Ian Adams (isa3)
 * Date: March 11, 2017
 */

#ifndef LISTTESTER_H_
#define LISTTESTER_H_

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
	void testPrepend();
	void testInsert();
	void testInsertAfter();
	void testInsertBefore();
	void testEquality();
	void testReadFromStream();
	void testWriteToString();
	void testInequality();
	void testOstream();
	void testWriteToStream();
	void testReadFromString();
	void testGetIndexOf();
	void testRemove();
};

#endif /*LISTTESTER_H_*/
