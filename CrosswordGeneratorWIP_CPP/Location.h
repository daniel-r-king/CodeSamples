#pragma once
#include <string>
class Location
{
private:
	int r;
	int c;
public:
	Location();
	Location(int r, int c);
	bool operator==(const Location location);
	bool operator!=(const Location location);

	int getR();
	int getC();

	void setR(int r);
	void setC(int c);

	std::string toString();
};

