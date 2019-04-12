   /* PlayListManager.h declares class PlayListManager.
    * Student Name: Shion Fukuzawa
    * Date: February 09
    */

#ifndef PLAYLISTMANAGER_H_
#define PLAYLISTMANAGER_H_

#include "PlayList.h"

class PlayListManager {
public:
	PlayListManager(const string& fileName);
	void run();  // Begin playlist manager

	// Main loop methods
	void printOptions() const;
	void readCommand();
	void executeCommand();


private:
	// Actions for each command
	void searchPlayListByArtist() const;  // Command 1
	void searchPlayListByYear() const;    // Command 2
	void searchPlayListByTitle() const;   // Command 3
	void addSongToPlayList();             // Command 4
	void removeSongFromPlayList();        // Command 5
	void printMyPlayList() const;         // Command 6
	void saveMyPlayList();                // Command 7
	void quit();                          // Command 0
	void printErrorMessage() const;       // Command default

	// Print methods for aesthetics
	void printLine() const;
	void printSongVector(const vector<Song> songs) const;

private:
	bool _quit;
	bool _edited;
	unsigned myCommand;
	PlayList myPlayList;
};

#endif /* PLAYLISTMANAGER_H_ */
