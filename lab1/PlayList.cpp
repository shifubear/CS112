   /* PlayList.cpp defines the PlayList methods.
    * Student Name: Shion Fukuzawa
    * Date: February 07
    * Begun by: Joel Adams, for CS 112 at Calvin College.
    */

#include "PlayList.h"
#include <fstream>
#include <cassert>
using namespace std;

/* PlayList constructor
* @param: fileName, a string
* Precondition: fileName contains the name of a playlist file.
*/
PlayList::PlayList(const string& fileName) {
	// open a stream to the playlist file
	ifstream fin( fileName.c_str() );
	assert( fin.is_open() );

	// read each song and append it to mySongs
	Song s;
	while (true) {
		s.readFrom(fin);
		if ( !fin ) { break; }
		string separator;
		getline(fin, separator);
		mySongs.push_back(s);
	}

	// close the stream
	fin.close();

	myFileName = fileName;
}

/* Retrieve length of the playlist
* Return: the number of songs in the playlist.
*/
unsigned PlayList::getNumSongs() const {
	return mySongs.size();
}

/* Get the list of songs in playlist
 * Return: A vector of songs included in the playlist.
 */
vector<Song> PlayList::getMySongs() const {
	return mySongs;
}

/* Search by artist
 * @param: artist, a string.
 * Return: a vector containing all the Songs in mySongs by artist.
 */
vector<Song> PlayList::searchByArtist(const string& artist) const {
   vector<Song> v;

   for (unsigned i = 0; i < mySongs.size(); i++) {
      if ( mySongs[i].getArtist().find(artist) != string::npos ) {
         v.push_back( mySongs[i] );
      }
   }

   return v;
}

/* Search by year
 * @param: year, an integer
 * Return: a vector containing all the Songs in mySongs created in year.
 */
vector<Song> PlayList::searchByYear(int year) const {
	vector<Song> v;

	for (unsigned i = 0; i < mySongs.size(); i++) {
		if ( mySongs[i].getYear() == year) {
			v.push_back( mySongs[i] );
		}
	}

	return v;
}

/* Search by title phrase
 * @param: phrase, a string
 * Return: a vector containing all Songs in mySongs with phrase in their title.
 */
vector<Song> PlayList::searchByTitlePhrase(const string& phrase) const {
	vector<Song> v;

	for (unsigned i = 0; i < mySongs.size(); i++) {
		if ( mySongs[i].getTitle().find(phrase) != string::npos ) {
			v.push_back( mySongs[i] );
		}
	}

	return v;
}

/* Adds new song to mySongs
 * @param: newSong, Song object to store in mySongs
 */
void PlayList::addSong(const Song& newSong) {
	mySongs.push_back(newSong);
}

/* Removes a song from mySongs
 * @param: aSong, Song object to remove from mySongs
 */
void PlayList::removeSong(const Song& aSong) {
	for (unsigned i = 0; i < mySongs.size(); i++) {
		if (mySongs[i] == aSong) {
			mySongs.erase(mySongs.begin() + i);
		}
	}
}

/* Saves the playlist to associated textfile
 */
void PlayList::save() const {
	ofstream fout(myFileName.c_str());

	for (unsigned i = 0; i < mySongs.size(); i++) {
		mySongs[i].writeTo(fout);
	}

	fout.close();
}
