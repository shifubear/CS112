/*
 * PalindromeDetectorTester.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: sf27
 */

#include "PalindromeDetectorTester.h"
#include "PalindromeDetector.h"
#include <iostream>
#include <cassert>
using namespace std;

void PalindromeDetectorTester::runTests() {
	cout << "Testing class PalindromeDetector..." << endl;

	testIsPalindrome();

	PalindromeDetector pd;
	pd.detectPalindromes("drawnOnward.txt");

	cout << "All tests passed!\n" << endl;
}

void PalindromeDetectorTester::testIsPalindrome() {
	cout << "Testing isPalindrome()... " << flush;
	PalindromeDetector pd;

	assert( !pd.isPalindrome("Hello") );
	cout << " 0 " << flush;

	assert( pd.isPalindrome("tacocat") );
	cout << " 1 " << flush;

	assert( !pd.isPalindrome("\n") );
	cout << " 2 " << flush;

	assert( !pd.isPalindrome(" ") );
	cout << " 3 " << flush;

	assert( pd.isPalindrome("Madam, I'm Adam") );
	cout << " 4 " << flush;

	cout << " Passed!" << endl;
}
