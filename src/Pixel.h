#pragma once
#include <fstream>
using std::ifstream;

class Pixel
{
	unsigned char redValue;
	unsigned char greenValue;
	unsigned char blueValue;

public:

	Pixel();
	unsigned char GetR();
	unsigned char GetG();
	unsigned char GetB();
	void SetR(unsigned char red);
	void SetG(unsigned char green);
	void SetB(unsigned char blue);

	void Add(float num, char color);
	void Multiply(float num, char color);
};