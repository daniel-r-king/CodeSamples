#include <vector>
#include "Tile.h"
#include "Word.h"
Word::Word(std::string letters) {
	for (int i = 0; i < letters.length(); i++) {
		Tile tile = Tile(letters[i]);
		tiles.push_back(tile);
	}
	orientation = -1;
}
Word::Word(std::vector<Tile> tiles) {
	this->tiles = tiles;
	orientation = -1;
}
std::vector<Tile> Word::getTiles() {
	return tiles;
}
int Word::getOrientation() {
	return orientation;
}
Tile* Word::tileAt(int index) {
	return &tiles[index];
}
void Word::setTiles(std::vector<Tile> tiles) {
	this->tiles = tiles;
}
void Word::setOrientation(int orientation) {
	this->orientation = orientation;
}
void Word::addTile(Tile tile) {
	tiles.push_back(tile);
}
void Word::addTile(char letter) {
	Tile tile = Tile(letter);
	tiles.push_back(tile);
}
int Word::length() {
	return tiles.size();
}
std::string Word::toString() {
	std::string str;
	for (int i = 0; i < tiles.size(); i++) {
		str += tiles[i].getLetter();
	}
	return str;
}
char Word::getRandomLetter() {
	return tiles[rand() % length()].getLetter();
}
int Word::getLetterIndex(char letter) {
	std::vector<int> indexes;
	for (int i = 0; i < length(); i++) {
		if (tiles[i].getLetter() == letter) {
			indexes.push_back(i);
		}
	}
	if (indexes.size() != 0) {
		return indexes[rand() % indexes.size()];
	}
	return -1;
}
bool Word::containsLetter(char letter) {
	for (int i = 0; i < length(); i++) {
		bool found = false;
		if (tiles[i].getLetter() == letter) {
			return true;
		}
	}
	return false;
}