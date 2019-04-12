/*
 * PalindromeDetector.h
 *
 *  Created on: Apr 11, 2017
 *      Author: sf27
 */

#ifndef PALINDROMEDETECTOR_H_
#define PALINDROMEDETECTOR_H_

#include <string>

class PalindromeDetector {
public:
	void detectPalindromes(const std::string& fp);

	bool isPalindrome(const std::string&);
};

#endif /* PALINDROMEDETECTOR_H_ */
