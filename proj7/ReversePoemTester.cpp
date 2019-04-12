/*
 * ReversePoemTester.cpp
 *
 *  Created on: Mar 31, 2017
 *      Author: sf27
 */

#include "ReversePoemTester.h"
#include <iostream>
#include <cassert>
using namespace std;

void ReversePoemTester::runTests() {
	cout << "Testing Stack class..." << endl;

	testConstructors();
	testGetters();

	cout << "All tests passed!" << endl;
}

void ReversePoemTester::testConstructors() {
	cout << " - constructors... " << flush;

	ReversePoem cats("cats.txt");
	assert( cats.myTitle == "Cats" );
	assert( cats.myAuthor == "Leo J. Smada" );
	assert( cats.myBody == "I love it when cats rub against me.\nI could never say\nI hate those purring felines.\n");
	cout << " 0 " << flush;

	cout << " Passed! " << endl;
}

void ReversePoemTester::testGetters() {
	cout << " - getters... " << flush;

	ReversePoem cats("cats.txt");
	assert( cats.getTitle() == "Cats" );
	cout << " 0 " << flush;
	assert( cats.getAuthor() == "Leo J. Smada" );
	cout << " 1 " << flush;
	assert( cats.getBody() == "I love it when cats rub against me.\nI could never say\nI hate those purring felines.\n");
	cout << " 2 " << flush;
	assert( cats.getBodyReversed() == "I hate those purring felines.\nI could never say\nI love it when cats rub against me.\n");
	cout << " 3 " << flush;

	cout << " Passed!" << endl;
}











