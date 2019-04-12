   /* Song.h declares a class for storing song information.
    * Student Name: Shion Fukuzawa
    * Date: February 07
    * Begun by: Joel Adams, for CS 112 at Calvin College.
    */
#ifndef SONG_H_
#define SONG_H_

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

class Song {
public:

	// Constructors
	Song();
	Song(const std::string& title, const std::string& artist, unsigned year);

	// Getters
	std::string getTitle() const;
	std::string getArtist() const;
	int getYear() const;

	// Methods
	void readFrom(std::istream& in);
    void writeTo(std::ostream& out) const;
    bool operator==(const Song& song2) const;

    void printSong() const;

private:
	std::string   myTitle;
	std::string   myArtist;
	unsigned myYear;
};

#endif /* SONG_H_ */
