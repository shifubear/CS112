/*
 * ReversePoem.h
 *
 *  Created on: Mar 28, 2017
 *      Author: sf27
 */

#ifndef REVERSEPOEM_H_
#define REVERSEPOEM_H_

#include "Stack.h"
#include <iostream>
#include <vector>
using namespace std;

class ReversePoem {
public:
	ReversePoem(const string& file);
	string getTitle() const;
	string getAuthor() const;
	string getBody() const;
	string getBodyReversed() const;

private:
	string myTitle;
	string myAuthor;
	string myBody;
	string myBodyReversed;
	Stack<string> myBodyStack;

	friend class ReversePoemTester;
};

#endif /* REVERSEPOEM_H_ */
