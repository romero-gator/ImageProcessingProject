#pragma once
#include <fstream>
#include "Pixel.h"
#include <vector>
using std::vector;
using std::ifstream;
using std::ofstream;

struct Header
{
	char idLength = 0;
	char colorMapType = 0;
	char dataTypeCode = 2;
	short colorMapOrigin = 0;
	short colorMapLength = 0;
	char colorMapDepth = 0;
	short xOrigin = 0;
	short yOrigin = 0;
	short width = 0;
	short height = 0;
	char bitsPerPixel = 24;
	char imageDescriptor = 0;
};

class Image
{
	vector<Pixel> pixels;
	Header header;

public:

	Image();
	short GetWidth();
	short GetHeight();
	void SetWidth(short w);
	void SetHeight(short h);

	void DeserializeHeader(ifstream& file);
	void DeserializeData(ifstream& file);
	void SerializeHeader(ofstream& file);
	void SerializeData(ofstream& file);
	void SerializeDataUpsideDown(ofstream& file);

	void Multiply(Image& top, Image& bottom);
	void Subtract(Image& top, Image& bottom);
	void Screen(Image& top, Image& bottom);
	void Overlay(Image& top, Image& bottom);
	void AddToChannel(float num, char color);
	void ScaleChannel(float num, char color);
	void WriteBChannel();
	void WriteGChannel();
	void WriteRChannel();
	void Combine(Image& red, Image& green, Image& blue);
	void Check(Image& img);
	void MakeBigImage(Image& img1, Image& img2, Image& img3, Image& img4);
};

