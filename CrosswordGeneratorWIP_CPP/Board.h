#pragma once
#include <string>
#include <vector>
#include "Word.h"
class Board
{
private:
	std::vector<std::vector<std::string>> matrix;
	std::vector<Word> words;
public:
	Board();

	std::vector<std::vector<std::string>> getBoard();
	std::vector<Word> getWords();

	void setBoard(std::vector<std::vector<std::string>> board);
	void setWords(std::vector<Word> words);

	Tile* getIntersectionTile(Word* wordA, Word wordB);
	Location getStartLocation(Tile interLetter, Word word);

	bool isOOB(Word word, Location location, int orientation);
	bool placementValid(Word word, Location location, int orientation);
	bool addWord(Word* word, Location location, int orientation);
	void printBoard();
	void clear();
};

