#include <chrono>
#include <iostream>
#include "Board.h"
#include "Constants.h"
#include "Game.h"
#include "Location.h"
#include "Test.h"
#include "Tile.h"
#include "Word.h"

void TEST_runTest(std::string testName, bool(*test)()) {
	_CrtMemState s1;
	_CrtMemState s2;
	_CrtMemState s3;
	_CrtMemCheckpoint(&s1);
	bool pass = test();
	_CrtMemCheckpoint(&s2);
	if (_CrtMemDifference(&s3, &s2, &s1)) {
		pass = false;
		std::cout << testName << " failed: MEMORY LEAK DETECTED" << std::endl;
		_CrtMemDumpStatistics(&s3);
	}
	if (pass) {
		std::cout << testName << " passed" << std::endl;
	}
}
void TEST_runAll() {
	TEST_runTest("TEST_Location()", TEST_Location);
	TEST_runTest("TEST_Tile()", TEST_Tile);
	TEST_runTest("TEST_Word()", TEST_Word);
	TEST_runTest("TEST_Board()", TEST_Board);
	TEST_runTest("TEST_Game()", TEST_Game);
}
bool TEST_Location() {
	bool pass = true;
	Location loc = Location(7, 3);
	int r = loc.getR();
	int c = loc.getC();
	if (r != 7) {
		pass = false;
		std::cout << "TEST_Location() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (c != 3) {
		pass = false;
		std::cout << "TEST_Location() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	loc.setR(5);
	loc.setC(2);
	if (loc.getR() != 5) {
		pass = false;
		std::cout << "TEST_Location() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (loc.getC() != 2) {
		pass = false;
		std::cout << "TEST_Location() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	return pass;
}
bool TEST_Tile() {
	bool pass = true;
	Tile tileA = Tile();
	tileA.setLetter('a');
	Location loc = Location(1, 3);
	tileA.setLocation(loc);
	if (tileA.getLetter() != 'a') {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileA.getLocation().getR() != 1) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileA.getLocation().getC() != 3) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	Tile tileB = Tile('b');
	tileB.setLocation(4, 7);
	if (tileB.getLetter() != 'b') {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileB.getLocation().getR() != 4) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileB.getLocation().getC() != 7) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	loc.setR(8);
	loc.setC(6);
	Tile tileC = Tile('c', loc);
	if (tileC.getLetter() != 'c') {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileC.getLocation().getR() != 8) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileC.getLocation().getC() != 6) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	loc.setR(10);
	loc.setC(1);
	Tile tileD(loc);
	if (tileD.getLetter() != ' ') {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileD.getLocation().getR() != 10) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileD.getLocation().getC() != 1) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	Tile tileE(25, 0);
	if (tileE.getLetter() != ' ') {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileE.getLocation().getR() != 25) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileE.getLocation().getC() != 0) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	Tile tileF('q', 100, 101);
	if (tileF.getLetter() != 'q') {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileF.getLocation().getR() != 100) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tileF.getLocation().getC() != 101) {
		pass = false;
		std::cout << "TEST_Tile() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	return pass;
}
bool TEST_Word() {
	bool pass = true;
	Word wordA = Word("test");
	Tile tileE = Tile('e');
	wordA.addTile(tileE);
	wordA.addTile('d');
	if (wordA.toString() != "tested") {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(0)->getLetter() != 't' || wordA.getTiles()[0].getLetter() != 't') {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(1)->getLetter() != 'e' || wordA.getTiles()[1].getLetter() != 'e') {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(2)->getLetter() != 's' || wordA.getTiles()[2].getLetter() != 's') {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(3)->getLetter() != 't' || wordA.getTiles()[3].getLetter() != 't') {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(4)->getLetter() != 'e' || wordA.getTiles()[4].getLetter() != 'e') {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(5)->getLetter() != 'd' || wordA.getTiles()[5].getLetter() != 'd') {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	Word wordB = Word(wordA.getTiles());
	if (wordB.toString() != "tested") {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordB.length() != 6) {
		pass = false;
		std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	char letter = wordB.getRandomLetter();
	for (int i = 0; i < 10; i++) {
		if (letter != 't' && letter != 'e' && letter != 's' && letter != 'd') {
			pass = false;
			std::cout << "TEST_Word() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
		}
	}
	return pass;
}
bool TEST_Board() {
	bool pass = true;
	Board board = Board();
	Word wordA = Word("test");
	board.addWord(&wordA, Location(0,0), VERTICAL);
	if (wordA.tileAt(0)->getLocation() != Location(0,0)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(1)->getLocation() != Location(1, 0)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(2)->getLocation() != Location(2, 0)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.tileAt(3)->getLocation() != Location(3, 0)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (wordA.toString() != "test") {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (board.getWords().size() != 0) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	for (int i = 0; i < board.getBoard().size(); i++) {
		for (int j = 0; j < board.getBoard()[i].size(); j++) {
			if (board.getBoard()[i][j] != TILE_SPACE) {
				pass = false;
				std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
			}
		}
	}
	Word wordB = Word("hello");
	if (board.addWord(&wordB, Location(STD_BOARD_HEIGHT - 1, STD_BOARD_WIDTH - 1), HORIZONTAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (board.addWord(&wordB, Location(STD_BOARD_HEIGHT - 1, STD_BOARD_WIDTH - 1), VERTICAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (!board.addWord(&wordB, Location(0,0), VERTICAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (!board.addWord(&wordB, Location(0,0), HORIZONTAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (!board.addWord(&wordB, Location(0,5), HORIZONTAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (board.addWord(&wordB, Location(0,6), HORIZONTAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (!board.addWord(&wordB, Location(5,0), VERTICAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	if (board.addWord(&wordB, Location(6,0), VERTICAL)) {
		pass = false;
		std::cout << "TEST_Board() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	wordA = Word("vector");
	wordB = Word("true");
	wordB.setOrientation(VERTICAL);
	board.addWord(&wordA, Location(1, 1), HORIZONTAL);
	Tile interTile = *board.getWords()[0].tileAt(5);
	Location loc = board.getStartLocation(interTile, wordB);
	if (loc != Location(0, 6)) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	wordA = Word("vector");
	wordB = Word("stop");
	wordB.setOrientation(HORIZONTAL);
	board.addWord(&wordA, Location(1, 2), VERTICAL);
	interTile = *board.getWords()[0].tileAt(4);
	loc = board.getStartLocation(interTile, wordB);
	if (loc != Location(5, 0)) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	board.clear();
	wordA = Word("heavy");
	wordB = Word("gloat");
	board.addWord(&wordA, Location(4, 1), HORIZONTAL);
	Tile* tile = board.getIntersectionTile(&wordA, wordB);
	if (tile->getLetter() != 'a') {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	if (tile->getLocation() != Location(4, 3)) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	return pass;
}
bool TEST_Game() {
	bool pass = true;
	Game game = Game();
	Word word = game.getRandomWord('a');
	if (!word.containsLetter('a')) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord('b');
	if (!word.containsLetter('b')) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord('c');
	if (!word.containsLetter('c')) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord(2);
	if (word.length() != 2) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord(4);
	if (word.length() != 4) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord(8);
	if (word.length() != 8) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord('a', 5);
	if (!word.containsLetter('a') || word.length() != 5) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord('b', 7);
	if (!word.containsLetter('b') || word.length() != 7) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord('c', 3);
	if (!word.containsLetter('c') || word.length() != 3) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	word = game.getRandomWord('z', INT_MAX);
	if (!word.containsLetter('*')) {
		pass = false;
		std::cout << "TEST_Game() failed at " << __FILE__ << "::" << __LINE__ << std::endl;
	}
	return pass;
}