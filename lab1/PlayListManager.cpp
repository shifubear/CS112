   /* PlayListManager.cpp defines the PlayListManager manager methods.
    * Student Name: Shion Fukuzawa
    * Date: February 09
    */

#include "PlayListManager.h"
#include <iostream>
#include <string>
using namespace std;

/* Explicit constructor for play list manager
 * @param: fileName, the name of the playlist file.
 *
 */
PlayListManager::PlayListManager(const string& fileName)
	: myPlayList(fileName) {
	_quit = false;
	_edited = false;
	myCommand = -1;
}

/* Runs Play List Manager.
 * The main loop repeats printing instructions, reading a command, and executing the command.
 */
void PlayListManager::run() {
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "Welcome to the PlayList Manager!" << endl;

	while (!_quit) {
		printOptions();
		readCommand();
		executeCommand();
	}
}

/* First method in main loop
 * This method prints the options
 */
void PlayListManager::printOptions() const {
	cout << "Please enter: \n" <<
			"\t1 - to search the playlist for songs by a given artist\n" <<
			"\t2 - to search the playlist for songs from a given year\n" <<
			"\t3 - to search the playlist for songs with a given phrase in their title\n" <<
			"\t4 - to add a new song to the playlist\n" <<
			"\t5 - to remove a song from the playlist\n" <<
			"\t6 - to see all songs in the playlist\n" << flush;
	if (_edited) {
		cout <<
			"\t7*- to save your playlist\n" << flush;
	} else {
		cout <<
			"\t7 - to save your playlist\n" << flush;
	}
	cout <<	"\t0 - to quit\n"
			"---> " << flush;

}

/* Second method in main loop
 * Reads a command from the keyboard. If the command is invalid, the main loop will restart.
 */
void PlayListManager::readCommand() {
	string input;
	cin >> input;
	if (input.length() != 1) {
		cout << "Invalid input!!! Try again..." << endl;
		// INVALID INPUT
	} else {
		myCommand = atoi(input.c_str());
	}
}

/* Third method in main loop
 * Performs an action based on input.
 */
void PlayListManager::executeCommand() {
	switch (myCommand) {
	case 1:
		searchPlayListByArtist();
		break;
	case 2:
		searchPlayListByYear();
		break;
	case 3:
		searchPlayListByTitle();
		break;
	case 4:
		addSongToPlayList();
		break;
	case 5:
		removeSongFromPlayList();
		break;
	case 6:
		printMyPlayList();
		break;
	case 7:
		saveMyPlayList();
		break;
	case 0:
		quit();
		break;
	case 404:
		break;
	default:
		printErrorMessage();
		break;
	}
}

/* Uses member PlayList to search desired artist name.
 *
 */
void PlayListManager::searchPlayListByArtist() const {
	string artist;
	printLine();
	cout << "What is the name of the artist you are looking for? -> " << flush;
	cin >> artist;
	cout << endl;
	vector<Song> results = myPlayList.searchByArtist(artist);
	cout << endl;

	if (results.size() == 0) {
		cout << "Sorry, could not find any songs by that artist!" << endl;
		printLine();
		return;
	}
	cout << "Found " << results.size() << " matches!" << endl << endl;
	printSongVector(results);

	printLine();
}

/* Uses member PlayList to search desired song by year.
 *
 */
void PlayListManager::searchPlayListByYear() const {
	unsigned year;
	printLine();
	cout << "What year? -> " << flush;
	cin >> year;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Invalid input!!! Try again." << endl;
		printLine();
		return;
	}
	cout << endl;
	vector<Song> results = myPlayList.searchByYear(year);
	cout << endl;

	if (results.size() == 0) {
		cout << "Sorry, could not find any songs from that year!" << endl;
		printLine();
		return;
	}
	cout << "Found " << results.size() << " matches!" << endl << endl;
	printSongVector(results);

	printLine();
}

/* Uses member PlayList to search desired song by title
 *
 */
void PlayListManager::searchPlayListByTitle() const {
	string title;
	printLine();
	cout << "What is the title? -> " << flush;
	cin >> title;
	cout << endl;
	vector<Song> results = myPlayList.searchByTitlePhrase(title);
	cout << endl;

	if (results.size() == 0) {
		cout << "Sorry, could not find any songs with that word in the title!" << endl;
		printLine();
		return;
	}
	cout << "Found " << results.size() << " matches!" << endl << endl;
	printSongVector(results);

	printLine();
}

/* Adds input song to current playlist.
 *
 */
void PlayListManager::addSongToPlayList() {
	string title,
		   artist;
	unsigned year;
	printLine();
	cout << "What is the title of the new song? -> " << flush;
	cin >> title;
	cout << "Who is the artist of the new song? -> " << flush;
	cin >> artist;
	cout << "When was the song released? -> " << flush;
	cin >> year;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Invalid input!!! Try again..." << endl;
		printLine();
		return;
	}

	Song newSong(title, artist, year);

	cout << endl
			<< "Is this the song you want to add?: " << endl;
	newSong.printSong();
	cout << "(y/n) > " << flush;
	string confirm;
	cin >> confirm;
	if (confirm == "y" || confirm == "Y") {
		myPlayList.addSong(newSong);
		_edited = true;
		cout << "Song added!" << endl;
	} else {
		cout << "Did not add song." << endl;
	}

	printLine();
}

/* Removes desired song from PlayList. If the song doesn't exist, prompts user and goes back to beginning of loop.
 *
 */
void PlayListManager::removeSongFromPlayList() {
	string title,
		   artist;
	unsigned year;
	printLine();
	cout << "What is the title of the song to remove? -> " << flush;
	cin >> title;
	cout << "Who is the artist of the song to remove? -> " << flush;
	cin >> artist;
	cout << "When was the song released? -> " << flush;
	cin >> year;
	if (cin.fail()) {
		cin.clear();
		cin.ignore();
		cout << "Invalid input!!! Try again..." << endl;
		printLine();
		return;
	}

	Song aSong(title, artist, year);

	bool songFound = false;
	for (unsigned i = 0; i < myPlayList.getMySongs().size(); i++) {
		if (aSong == myPlayList.getMySongs()[i]) {
			songFound = true;
			break;
		}
	}
	if (songFound) {
		cout << endl
				<< "Are you sure you want to remove this song?: " << endl;
		aSong.printSong();
		cout << "(y/n) > " << flush;
		string confirm;
		cin >> confirm;
		if (confirm == "y" || confirm == "Y") {
			myPlayList.removeSong(aSong);
			_edited = true;
			cout << "Song removed!" << endl;
		} else {
			cout << "Did not remove song." << endl;
		}
	} else {
		cout << endl
				<< "Could not find the song!!!" << endl;
	}
	printLine();
}

/* Convenience method to print a playlist.
 *
 */
void PlayListManager::printMyPlayList() const {
	printLine();
	cout << "Your Playlist!! " << endl << endl;
	printSongVector(myPlayList.getMySongs());
	printLine();
}

/* Saves current playlist to file.
 *
 */
void PlayListManager::saveMyPlayList() {
	printLine();
	string command;
	cout << "Are you sure you want to save this PlayList? (y/n) -> " << flush;
	cin >> command;
	if (command == "y" || command == "Y") {
		cout << "Saving playlist..." << endl << endl;
		myPlayList.save();
		_edited = false;
		cout << "Saved!" << endl;
	} else {
		cout << "Not saving playlist." << endl;
	}
	printLine();
}

/* Quits the play list manager by setting quit flag to true.
 *
 */
void PlayListManager::quit() {
	printLine();
	if (_edited) {
		cout << "You have unsaved changes in your playlist!" << endl
				<< "Are you sure you want to quit? (y/n) > " << flush;
		string command;
		cin >> command;
		if (command != "y" || command != "Y") {
			cout << "Cancelled quitting..." << endl;
			printLine();
			return;
		}
	}
	cout << "See you next time!" << endl;
	printLine();
	_quit = true;
}

/* Prints error message when user inputs an invalid command.
 *
 */
void PlayListManager::printErrorMessage() const {
	printLine();
	cout << "That is not a valid command!!! Try again..." << endl;\
	printLine();
}

/* Prints a line to make the output look pretty.
 *
 */
void PlayListManager::printLine() const {
	cout << endl
			<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl
			<< endl;
}

/* Convenience method to print a vector of songs.
 * Reduces duplicated code and makes the output consistent.
 */
void PlayListManager::printSongVector(const vector<Song> songs) const {
	for (unsigned i = 0; i < songs.size(); i++) {
		songs[i].printSong();
		cout << endl;
	}
}









