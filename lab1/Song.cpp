   /* Song.cpp defines the methods for class Song (see Song.h).
    * Student Name: Shion Fukuzawa
    * Date: February 07
    * Begun by: Joel Adams, for CS 112 at Calvin College.
    */
#include "Song.h"

/* Song default constructor
 * Postcondition: myTitle and myArtist are empty strings
 *            && myYear == 0.
 */
Song::Song() {
  myTitle = myArtist = "";
  myYear = 0;
}

/* Explicit constructor
 * @param: title, a string
 * @param: artist, a string
 * @year: an unsigned int.
 * Postcondition: myTitle == title &&
 *                myArtist == artist &&
 *                myYear == year.
 */
Song::Song(const std::string& title, const std::string& artist, unsigned year) {
	myTitle = title;
	myArtist = artist;
	myYear = year;
}


/* getter method for myTitle
 * Return: myTitle
 */
std::string Song::getTitle() const {
  return myTitle;
}

/* getter method for myArtist
 * Return: myArtist
 */
std::string Song::getArtist() const {
  return myArtist;
}

/* getter method for myYear
 * Return: myYear
 */
int Song::getYear() const {
  return myYear;
}

/* Song input method...
 * @param: in, an istream
 * Precondition: in contains the title, artist, and year data for a Song.
 * Postcondition: the title, artist, and year data have been read from in &&
 *                 myTitle == title &&
 *                 myArtist == artist &&
 *                 myYear == year.
 */
void Song::readFrom(std::istream& in) {
   getline(in, myTitle);
   getline(in, myArtist);
   std::string yearString;
   getline(in, yearString);
   myYear = atoi( yearString.c_str() );
}

/* Song output...
 * @param: out, an ostream
 * Postcondition: out contains myTitle, a newline,
 *                             myArtist, a newline,
 *                             myYear, and a newline.
 */
void Song::writeTo(std::ostream& out) const {
	out << myTitle << '\n'
	    << myArtist << '\n'
	    << myYear  << '\n' << '\n';
}

/* Song equality operator...
 * @param: song2, another song to compare to.
 * Postcondition: returns true if both songs have the same title, artist, and year.
 */
bool Song::operator==(const Song& song2) const {
	return (getTitle() == song2.getTitle()) && (getArtist() == song2.getArtist()) && (getYear() == song2.getYear());
}

/* Prints the song information to console
 *
 */
void Song::printSong() const {
	std::cout << myTitle << '\n'
			<< myArtist << '\n'
			<< myYear << '\n' << std::flush;
}
