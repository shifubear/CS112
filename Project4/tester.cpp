/* tester.cpp drives the testing of our Vec template and Matrix class.
 * Student: Shion Fukuzawa, Carlos Payer
 * Date: March 04, 2017
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 */

#include "MatrixTester.h"
#include "MatrixApplication.h"

int main() {
	MatrixTester mt;
	mt.runTests();

	MatrixApplication ma;
	ma.run();
}
