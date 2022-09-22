#pragma once
#include "Board.h"
#include "Location.h"
#include "Word.h"
class Game
{
private:
	Board board;
	std::vector<std::string> wordBank;
public:
	Game();

	Board* getBoard();
	std::vector<std::string>* getWordBank();

	void setBoard(Board board);
	void setWordBank(std::vector<std::string> wordBank);

	Word getRandomWord(char letter);
	Word getRandomWord(int length);
	Word getRandomWord(char letter, int length);

	bool generatePuzzle(int nWords, int maxLength);
};

