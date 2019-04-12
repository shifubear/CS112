/*
 * HeightExperiment.cpp
 *
 *  Created on: Apr 18, 2017
 *      Author: sf27
 */

#include "BST.h"
#include "HeightExperiment.h"

#include <fstream>
#include <cassert>
#include <string>
#include <stdexcept>
#include <cstdlib>
using namespace std;

void HeightExperiment::run() {

	cout << "Beginning Height Experiment... " << endl;

	string dir = "/home/cs/112/proj/09/randomInts";

	for (int i = 1; i <= 10; i++) {
		string fname;
		cout << "Calculating height for BST number " << i << endl;
		if (i < 10)
			fname = dir + "0" + to_string(i) + ".txt";
		else
			fname = dir + to_string(i) + ".txt";

		getHeightOf(fname);

		cout << endl << endl;
	}
}

void HeightExperiment::getHeightOf(const string& fname) {
	ifstream fin(fname.c_str());
	assert(fin.is_open());

	BST<long> bst;

	int duplicates = 0;
	int numCount = 0;
	string line;
	string::size_type sz;
	while (!fin.eof()) {
		numCount++;
		getline(fin, line);
		long num;
		try {
			num = atol(line.c_str());
		} catch (invalid_argument& ia) {
			break;
		}
		
		try{
			bst.insert(num);
		} catch (Exception& ex) {
			duplicates++;
		}

	}

	cout << "The height of this BST is " << bst.getHeight() << endl;
	cout << "There were " << numCount << " numbers processed." << endl;
	cout << "There are " << bst.getNumItems() << " numbers in the BST." << endl;
	cout << "The number of duplicates in this set of numbers was " << duplicates << endl;
}
