/*
 * ReversePoem.cpp
 *
 *  Created on: Mar 28, 2017
 *      Author: sf27
 */

#include "ReversePoem.h"
#include "Stack.h"
#include <iostream>
#include <fstream>
#include <cassert>

ReversePoem::ReversePoem(const string& fName)
: myBodyStack(1){
	ifstream myfile(fName.c_str());
	assert( myfile.is_open() );
	string line;
	getline(myfile, line);
	myTitle = line;
	getline(myfile, line);
	myAuthor = line;

	getline(myfile, line); // For the empty line

	while ( getline (myfile, line) ) {
		string newLine = line + '\n';
		myBody += newLine;
		try {
			myBodyStack.push(newLine);
		} catch( StackException& se ) {
			myBodyStack.setCapacity(myBodyStack.getCapacity() * 2);
			myBodyStack.push(newLine);
		}
	}

	while (!myBodyStack.isEmpty())
		myBodyReversed += myBodyStack.pop();

	myfile.close();
}


string ReversePoem::getTitle() const {
	return myTitle;
}

string ReversePoem::getAuthor() const {
	return myAuthor;
}

string ReversePoem::getBody() const {
	return myBody;
}

string ReversePoem::getBodyReversed() const {
	return myBodyReversed;
}






