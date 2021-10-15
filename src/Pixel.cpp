#include "Pixel.h"
#include <iostream>
using std::cout;
using std::endl;

Pixel::Pixel()
{
	redValue = 0;
	greenValue = 0;
	blueValue = 0;
}
unsigned char Pixel::GetR()
{
	return redValue;
}
unsigned char Pixel::GetG()
{
	return greenValue;
}
unsigned char Pixel::GetB()
{
	return blueValue;
}
void Pixel::SetR(unsigned char red)
{
	redValue = red;
}
void Pixel::SetG(unsigned char green)
{
	greenValue = green;
}
void Pixel::SetB(unsigned char blue)
{
	blueValue = blue;
}

void Pixel::Add(float num, char color)
{
	float tempNum;

	if (color == 'B' || color == 'b')
	{
		tempNum = (float)blueValue;
		tempNum += num;
		if (tempNum > 255)
		{
			tempNum = 255;
		}
		blueValue = (unsigned char)tempNum;
	}
	else if (color == 'G' || color == 'g')
	{
		tempNum = (float)greenValue;
		tempNum += num;
		if (tempNum > 255)
		{
			tempNum = 255;
		}
		greenValue = (unsigned char)tempNum;
	}
	else if (color == 'R' || color == 'r')
	{
		tempNum = (float)redValue;
		tempNum += num;
		if (tempNum > 255)
		{
			tempNum = 255;
		}
		redValue = (unsigned char)tempNum;
	}
}
void Pixel::Multiply(float num, char color)
{
	float tempNum;

	if (color == 'B' || color == 'b')
	{
		tempNum = (float)blueValue;
		tempNum = tempNum * num;
		if (tempNum > 255)
		{
			tempNum = 255;
		}
		blueValue = (unsigned char)tempNum;
	}
	else if (color == 'G' || color == 'g')
	{
		tempNum = (float)greenValue;
		tempNum = tempNum * num;
		if (tempNum > 255)
		{
			tempNum = 255;
		}
		greenValue = (unsigned char)tempNum;
	}
	else if (color == 'R' || color == 'r')
	{
		tempNum = (float)redValue;
		tempNum = tempNum * num;
		if (tempNum > 255)
		{
			tempNum = 255;
		}
		redValue = (unsigned char)tempNum;
	}
}