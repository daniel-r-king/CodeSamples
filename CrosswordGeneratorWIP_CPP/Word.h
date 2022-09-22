#pragma once
#include <string>
#include <vector>
#include "Tile.h"
class Word
{
private:
	std::vector<Tile> tiles;
	int orientation;
public:
	Word(std::string letters);
	Word(std::vector<Tile> tiles);

	std::vector<Tile> getTiles();
	int getOrientation();
	Tile* tileAt(int index);

	void setTiles(std::vector<Tile> tiles);
	void setOrientation(int orientation);

	void addTile(Tile tile);
	void addTile(char letter);

	int length();
	std::string toString();

	char getRandomLetter();
	int getLetterIndex(char letter);

	bool containsLetter(char letter);
};

