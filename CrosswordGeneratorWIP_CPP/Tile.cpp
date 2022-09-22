#include "Location.h"
#include "Tile.h"
Tile::Tile() {
	letter = ' ';
	location = Location(0,0);
}
Tile::Tile(char letter) {
	this->letter = letter;
	location = Location(0,0);
}
Tile::Tile(Location location) {
	letter = ' ';
	this->location = location;
}
Tile::Tile(int r, int c) {
	letter = ' ';
	location = Location(r,c);
}
Tile::Tile(char letter, Location location) {
	this->letter = letter;
	this->location = location;
}
Tile::Tile(char letter, int r, int c) {
	this->letter = letter;
	location = Location(r,c);
}
char Tile::getLetter() {
	return letter;
}
Location Tile::getLocation() {
	return location;
}
void Tile::setLetter(char letter) {
	this->letter = letter;
}
void Tile::setLocation(Location location) {
	this->location = location;
}
void Tile::setLocation(int r, int c) {
	location = Location(r,c);
}
