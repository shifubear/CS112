   /* PlayListTester.cpp defines the PlayList test-methods.
    * Student Name: Shion Fukuzawa
    * Date: February 07
    * Begun by: Joel Adams, for CS 112 at Calvin College.
    */

#include "PlayListTester.h"
#include "PlayList.h"
#include <iostream>
#include <cassert>
using namespace std;

void PlayListTester::runTests() {
  cout << "\nTesting class PlayList..." << endl;
  testConstructors();
  testSearchByArtist();
  testSearchByYear();
  testSearchByTitlePhrase();
  testAddAndRemoveSong();
  testSave();
  cout << "All tests passed!" << endl;
}

void PlayListTester::testConstructors() {
	cout << "- constructors..." << flush;
	PlayList pList("testSongs.txt");
	assert( pList.getNumSongs() == 4 );
	cout << " 0 " << flush;

	cout << "Passed!" << endl;
}

void PlayListTester::testSearchByArtist() {
	cout << "- searchByArtist()... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	//empty case (0)
	vector<Song> searchResult = pList.searchByArtist("Cream");
	assert( searchResult.size() == 0 );
	cout << " 0 " << flush;

	// case of 1
	searchResult = pList.searchByArtist("Baez");
	assert( searchResult.size() == 1 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	cout << " 1 " << flush;

	// case of 2
	searchResult = pList.searchByArtist("Beatles");
	assert( searchResult.size() == 2 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	assert( searchResult[1].getTitle() == "Penny Lane" );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testSearchByYear() {
	cout << "- searchByYear()... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	//empty case (0)
	vector<Song> searchResult = pList.searchByYear(2010);
	assert( searchResult.size() == 0 );
	cout << " 0 " << flush;

	// case of 1
	searchResult = pList.searchByYear(2012);
	assert( searchResult.size() == 1 );
	assert( searchResult[0].getTitle() == "Call Me Maybe" );
	cout << " 1 " << flush;

	// case of 2
	searchResult = pList.searchByYear(1967);
	assert( searchResult.size() == 2 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	assert( searchResult[1].getTitle() == "Penny Lane" );
	cout << " 2 " << flush;

	cout << " Passed!" << endl;
}

void PlayListTester::testSearchByTitlePhrase() {
	cout << "- searchByTitlePhrase()... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	//empty case (0)
	vector<Song> searchResult = pList.searchByTitlePhrase("Cream");
	assert( searchResult.size() == 0 );
	cout << " 0 " << flush;

	// case of 1
	searchResult = pList.searchByTitlePhrase(" Maybe");
	assert( searchResult.size() == 1 );
	assert( searchResult[0].getTitle() == "Call Me Maybe" );
	cout << " 1 " << flush;

	// case of 2
	searchResult = pList.searchByTitlePhrase("t I");
	assert( searchResult.size() == 2 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	assert( searchResult[1].getTitle() == "Let It Be" );
	cout << " 2 " << flush;

	// case of 3
	searchResult = pList.searchByTitlePhrase("L");
	assert( searchResult.size() == 3 );
	assert( searchResult[0].getTitle() == "Let It Be" );
	assert( searchResult[1].getTitle() == "Let It Be" );
	assert( searchResult[2].getTitle() == "Penny Lane" );
	cout << " 3 " << flush;

	cout << "Passed!" << endl;
}

void PlayListTester::testAddAndRemoveSong() {
	cout << "- addSong()... " << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	unsigned previousLength = pList.getNumSongs();
	Song newSong("Creep", "Radiohead", 1993);
	pList.addSong(newSong);
	assert( pList.getNumSongs() == previousLength + 1 );
	assert( pList.getMySongs()[previousLength].getTitle() == "Creep" );
	assert( pList.getMySongs()[previousLength].getArtist() == "Radiohead" );
	assert( pList.getMySongs()[previousLength].getYear() == 1993 );
	cout << " 0 " << flush;

	cout << "Passed!" << endl;

	cout << "- removeSong()... " << flush;
	pList.removeSong(newSong);
	assert( pList.getNumSongs() == previousLength );
	assert( pList.searchByTitlePhrase("Creep").size() == 0 );
	assert( pList.searchByArtist("Radiohead").size() == 0 );
	assert( pList.searchByYear(1993).size() == 0 );
	cout << " 0 " << flush;

	cout << "Passed!" << endl;
}

void PlayListTester::testSave() {
	cout << "- save()..." << flush;
	// load a playlist with test songs
	PlayList pList("testSongs.txt");

	pList.removeSong(Song("Penny Lane", "The Beatles", 1967));

	pList.save();

	PlayList newList("testSongs.txt");

	assert( newList.getNumSongs() == 3 );
	assert( newList.getMySongs()[0] == Song("Call Me Maybe", "Carly Rae Jepsen", 2012) );
	assert( newList.getMySongs()[1] == Song("Let It Be", "The Beatles", 1967) );
	assert( newList.getMySongs()[2] == Song("Let It Be", "Joan Baez", 1971) );
	cout << " 0 " << flush;

	newList.addSong(Song("Penny Lane", "The Beatles", 1967));

	newList.save();

	PlayList newerList("testSongs.txt");

	assert( newList.getNumSongs() == 4 );
	assert( newList.getMySongs()[0] == Song("Call Me Maybe", "Carly Rae Jepsen", 2012) );
	assert( newList.getMySongs()[1] == Song("Let It Be", "The Beatles", 1967) );
	assert( newList.getMySongs()[2] == Song("Let It Be", "Joan Baez", 1971) );
	assert( newList.getMySongs()[3] == Song("Penny Lane", "The Beatles", 1967) );
	cout << " 1 " << flush;

	cout << "Passed!" << endl;
}
