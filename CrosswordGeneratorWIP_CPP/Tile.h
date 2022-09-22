#pragma once
#include "Location.h"
class Tile
{
private:
	char letter;
	Location location;
public:
	Tile();
	Tile(char letter);
	Tile(Location location);
	Tile(int r, int c);
	Tile(char letter, Location location);
	Tile(char letter, int r, int c);

	char getLetter();
	Location getLocation();

	void setLetter(char letter);
	void setLocation(Location location);
	void setLocation(int r, int c);
};

