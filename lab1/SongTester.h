   /* SongTester.h declares a test-class for class Song.
    * Student Name: Shion Fukuzawa
    * Date: February 07
    * Begun by: Joel Adams, for CS 112 at Calvin College.
    */
#ifndef SONGTESTER_H_
#define SONGTESTER_H_

class SongTester {
public:
	void runTests();
	void testConstructors();
	void testReadFrom();
	void testWriteTo();
	void testEqualityOperator();
};

#endif /* SONGTESTER_H_ */
