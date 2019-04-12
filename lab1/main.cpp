/* main.cpp tests the classes in our project.
* Student Name: Shion Fukuzawa
* Date: February 07
* Begun by: Joel Adams, for CS 112 at Calvin College.
*/

#include "SongTester.h"
#include "PlayListTester.h"
#include "PlayListManager.h"

int main() {
   SongTester sTester;
   sTester.runTests();
   PlayListTester plTester;
   plTester.runTests();
   PlayListManager plm("testSongs.txt");
   plm.run();
}

/*
 * TODO:
 * 	Complete error handling in PLM
 */
