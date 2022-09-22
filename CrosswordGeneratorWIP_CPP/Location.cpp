#include "Location.h"
Location::Location() {
	r = 0;
	c = 0;
}
Location::Location(int r, int c) {
	this->r = r;
	this->c = c;
}
bool Location::operator==(const Location location) {
	if (r == location.r && c == location.c) {
		return true;
	}
	return false;
}
bool Location::operator!=(const Location location) {
	if (r == location.r && c == location.c) {
		return false;
	}
	return true;
}
int Location::getR() {
	return r;
}
int Location::getC() {
	return c;
}
void Location::setR(int r) {
	this->r = r;
}
void Location::setC(int c) {
	this->c = c;
}
std::string Location::toString() {
	return "(" + std::to_string(r) + "," + std::to_string(c) + ")";
}
