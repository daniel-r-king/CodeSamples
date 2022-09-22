#include <iostream>
#include "Board.h"
#include "Constants.h"
#include "Word.h"
Board::Board() {
	for (int i = 0; i < STD_BOARD_HEIGHT; i++) {
		std::vector<std::string> row;
		for (int j = 0; j < STD_BOARD_WIDTH; j++) {
			row.push_back(TILE_SPACE);
		}
		matrix.push_back(row);
	}
}
std::vector<std::vector<std::string>> Board::getBoard() {
	return matrix;
}
std::vector<Word> Board::getWords() {
	return words;
}
void Board::setBoard(std::vector<std::vector<std::string>> matrix) {
	this->matrix = matrix;
}
void Board::setWords(std::vector<Word> words) {
	this->words = words;
}
Tile* Board::getIntersectionTile(Word* wordA, Word wordB) {
	std::vector<Tile*> tiles;
	for (int i = 0; i < wordA->length(); i++) {
		for (int j = 0; j < wordB.length(); j++) {
			if (wordA->tileAt(i)->getLetter() == wordB.tileAt(j)->getLetter()) {
				tiles.push_back(wordA->tileAt(i));
			}
		}
	}
	return tiles[rand() % tiles.size()];
}
Location Board::getStartLocation(Tile interLetter, Word word) {
	int r;
	int c;
	int interLetterIndex = word.getLetterIndex(interLetter.getLetter());
	switch (word.getOrientation()) {
	case VERTICAL:
		r = interLetter.getLocation().getR() - interLetterIndex;
		c = interLetter.getLocation().getC();
		return Location(r, c);
		break;
	case HORIZONTAL:
		r = interLetter.getLocation().getR();
		c = interLetter.getLocation().getC() - interLetterIndex;
		return Location(r, c);
		break;
	}
	return Location(-1,-1);
}
bool Board::isOOB(Word word, Location origin, int orientation) {
	int spaceAvailable;
	if (origin.getR() < 0 || origin.getC() < 0) {
		return true;
	}
	switch (orientation) {
	case VERTICAL:
		spaceAvailable = STD_BOARD_HEIGHT - origin.getR();
		if (word.length() > spaceAvailable)
			return true;
		break;
	case HORIZONTAL:
		spaceAvailable = STD_BOARD_WIDTH - origin.getC();
		if (word.length() > spaceAvailable)
			return true;
		break;
	}
	return false;
}
bool Board::addWord(Word* word, Location origin, int orientation) {
	if (isOOB(*word, origin, orientation)) {
		return false;
	}
	int r = origin.getR();
	int c = origin.getC();
	switch (orientation) {
	case VERTICAL:
		for (int i = 0; i < word->length(); i++) {
			word->tileAt(i)->setLocation(r + i, c);
			matrix[r + i][c] = std::string({ '[', word->tileAt(i)->getLetter(), ']' });
		}
		word->setOrientation(orientation);
		words.push_back(*word);
		break;
	case HORIZONTAL:
		for (int i = 0; i < word->length(); i++) {
			word->tileAt(i)->setLocation(r, c + i);
			matrix[r][c + i] = std::string({ '[', word->tileAt(i)->getLetter(), ']' });
		}
		word->setOrientation(orientation);
		words.push_back(*word);
		break;
	}
	return true;
}
void Board::printBoard() {
	for (int i = 0; i < STD_BOARD_HEIGHT; i++) {
		for (int j = 0; j < STD_BOARD_WIDTH; j++) {
			std::cout << matrix[i][j];
		}
		std::cout << std::endl;
	}
}
void Board::clear() {
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			matrix[i][j] = TILE_SPACE;
		}
	}
	words.clear();
}
