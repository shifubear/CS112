/*
 * PalindromeDetector.cpp
 *
 *  Created on: Apr 11, 2017
 *      Author: sf27
 */

#include "PalindromeDetector.h"
#include "Stack.h"
#include "ArrayQueue.h"

#include <fstream>
#include <cassert>
using namespace std;

void PalindromeDetector::detectPalindromes(const string& fp) {
	ifstream fin( fp.c_str() );
	assert( fin.is_open() );
	string outFp = "out" + fp;
	ofstream fout( outFp.c_str() );
	assert( fout.is_open() );

	string line;
	while ( !fin.eof() ) {
		getline(fin, line);
		fout << line << flush;
		if (isPalindrome(line)) {
			fout << " ***";
		}
		fout << endl;
	}

	fin.close();
	fout.close();
}

bool PalindromeDetector::isPalindrome(const string& s) {

	Stack<char> stackLetters(1);
	ArrayQueue<char> queueLetters(1);
	for (int i = 0; i < s.length(); i++) {
		char c = s[i];
		if (65 <= c && c <= 90) {
			c += 32;
		}

		if (97 <= c && c <= 122) {
			try {
				stackLetters.push(c);
			} catch (StackException& se) {
				stackLetters.setCapacity(stackLetters.getCapacity() * 2);
				stackLetters.push(c);
			}

			try {
				queueLetters.append(c);
			} catch (QueueException& qe) {
				queueLetters.setCapacity(stackLetters.getCapacity() * 2);
				queueLetters.append(c);
			}
		}
	}

	if (stackLetters.isEmpty() && queueLetters.isEmpty() ) {
		return false;
	}

	while (!stackLetters.isEmpty() && !queueLetters.isEmpty()) {
		char ch1 = stackLetters.pop();
		char ch2 = queueLetters.remove();
		if (ch1 != ch2)
			return false;
	}

	return true;
}

