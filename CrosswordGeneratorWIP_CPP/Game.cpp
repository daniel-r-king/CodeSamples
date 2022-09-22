#include <iostream>
#include <fstream>
#include "Constants.h"
#include "Game.h"
Game::Game() {
	board = Board();
	std::ifstream input;
	input.open("words.txt");
	if (input.is_open()) {
		std::string str;
		while (std::getline(input, str)) {
			wordBank.push_back(str);
		}
	}
	else {
		std::cout << "ERROR: Failed to open input file." << std::endl;
	}
}
Board* Game::getBoard() {
	return &board;
}
std::vector<std::string>* Game::getWordBank() {
	return &wordBank;
}
void Game::setBoard(Board board) {
	this->board = board;
}
void Game::setWordBank(std::vector<std::string> wordBank) {
	this->wordBank = wordBank;
}
Word Game::getRandomWord(char letter) {
	std::vector<std::string> strings;
	for (int i = 0; i < wordBank.size(); i++) {
		for (int j = 0; j < wordBank[i].size(); j++) {
			bool found = false;
			if (wordBank[i][j] == letter) {
				found = true;
			}
			if (found) {
				strings.push_back(wordBank[i]);
			}
		}
	}
	if (strings.size() != 0) {
		return Word(strings[rand() % strings.size()]);
	}
	return Word("*");
}
Word Game::getRandomWord(int length) {
	std::vector<std::string> strings;
	for (int i = 0; i < wordBank.size(); i++) {
		if (wordBank[i].length() == length) {
			strings.push_back(wordBank[i]);
		}
	}
	if (strings.size() != 0) {
		return Word(strings[rand() % strings.size()]);
	}
	return Word("*");
}
Word Game::getRandomWord(char letter, int length) {
	std::vector<std::string> strings;
	for (int i = 0; i < wordBank.size(); i++) {
		for (int j = 0; j < wordBank[i].size(); j++) {
			if (wordBank[i].length() == length) {
				bool found = false;
				if (wordBank[i][j] == letter) {
					found = true;
				}
				if (found) {
					strings.push_back(wordBank[i]);
				}
			}
		}
	}
	if (strings.size() != 0) {
		return Word(strings[rand() % strings.size()]);
	}
	return Word("*");
}
bool Game::generatePuzzle(int nWords, int maxLength) {
	return true;
}