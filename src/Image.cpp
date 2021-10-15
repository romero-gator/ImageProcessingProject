#include "Image.h"
#include <iostream>
using std::cout;
using std::endl;

Image::Image()
{
	
}

short Image::GetWidth()
{
	return header.width;
}
short Image::GetHeight()
{
	return header.height;
}
void Image::SetWidth(short w)
{
	header.width = w;
}
void Image::SetHeight(short h)
{
	header.height = h;
}

void Image::DeserializeHeader(ifstream& file)
{
	file.read(&header.idLength, sizeof(header.idLength));
	file.read(&header.colorMapType, sizeof(header.colorMapType));
	file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
	file.read((char *)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
	file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
	file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
	file.read((char*)&header.width, sizeof(header.width));
	file.read((char*)&header.height, sizeof(header.height));
	file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));
}
void Image::DeserializeData(ifstream& file)
{
	int dataSize = header.width * header.height;
	for (unsigned int i = 0; i < dataSize; i++)
	{
		Pixel newPixel;
		unsigned char colorValue = 0;
		file.read((char*)&colorValue, sizeof(colorValue));
		newPixel.SetB(colorValue);
		file.read((char*)&colorValue, sizeof(colorValue));
		newPixel.SetG(colorValue);
		file.read((char*)&colorValue, sizeof(colorValue));
		newPixel.SetR(colorValue);
		pixels.push_back(newPixel);
	}
}
void Image::SerializeHeader(ofstream& file)
{
	file.write(&header.idLength, sizeof(header.idLength));
	file.write(&header.colorMapType, sizeof(header.colorMapType));
	file.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
	file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
	file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
	file.write((char*)&header.width, sizeof(header.width));
	file.write((char*)&header.height, sizeof(header.height));
	file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));
}
void Image::SerializeData(ofstream& file)
{
	for (unsigned int i = 0; i < pixels.size(); i++)
	{
		unsigned char colorValue = pixels[i].GetB();
		file.write((char*)&colorValue, sizeof(colorValue));
		colorValue = pixels[i].GetG();
		file.write((char*)&colorValue, sizeof(colorValue));
		colorValue = pixels[i].GetR();
		file.write((char*)&colorValue, sizeof(colorValue));
	}
}
void Image::SerializeDataUpsideDown(ofstream& file)
{
	for (int i = pixels.size() - 1; i >= 0; i--)
	{
		unsigned char colorValue = pixels[i].GetB();
		file.write((char*)&colorValue, sizeof(colorValue));
		colorValue = pixels[i].GetG();
		file.write((char*)&colorValue, sizeof(colorValue));
		colorValue = pixels[i].GetR();
		file.write((char*)&colorValue, sizeof(colorValue));
	}
}

void Image::Multiply(Image& top, Image& bottom)
{
	for (unsigned int i = 0; i < top.pixels.size(); i++)
	{
		Pixel newPixel;

		float num1 = top.pixels[i].GetB();
		float num2 = bottom.pixels[i].GetB();
		float result = ((num1 * num2) / 255) + 0.5f;

		newPixel.SetB((unsigned char)result);

		num1 = top.pixels[i].GetG();
		num2 = bottom.pixels[i].GetG();
		result = ((num1 * num2) / 255) + 0.5f;

		newPixel.SetG((unsigned char)result);

		num1 = top.pixels[i].GetR();
		num2 = bottom.pixels[i].GetR();
		result = ((num1 * num2) / 255) + 0.5f;

		newPixel.SetR((unsigned char)result);

		this->pixels.push_back(newPixel);
	}
}
void Image::Subtract(Image& top, Image& bottom)
{
	for (unsigned int i = 0; i < top.pixels.size(); i++)
	{
		Pixel newPixel;

		float num1 = top.pixels[i].GetB();
		float num2 = bottom.pixels[i].GetB();
		float result = num2 - num1;
		if (result < 0)
		{
			result = 0;
		}

		newPixel.SetB((unsigned char)result);

		num1 = top.pixels[i].GetG();
		num2 = bottom.pixels[i].GetG();
		result = num2 - num1;
		if (result < 0)
		{
			result = 0;
		}

		newPixel.SetG((unsigned char)result);

		num1 = top.pixels[i].GetR();
		num2 = bottom.pixels[i].GetR();
		result = num2 - num1;
		if (result < 0)
		{
			result = 0;
		}

		newPixel.SetR((unsigned char)result);

		this->pixels.push_back(newPixel);
	}
}
void Image::Screen(Image& top, Image& bottom)
{
	for (unsigned int i = 0; i < top.pixels.size(); i++)
	{
		Pixel newPixel;
		float num1, num2, result;

		num1 = (float) top.pixels[i].GetB();
		if (num1 == 0)
		{
			result = (float) bottom.pixels[i].GetB();
		}
		else if (num1 == 255)
		{
			result = 255;
		}
		else
		{
			num1 = (float)top.pixels[i].GetB() / 255;
			num2 = (float)bottom.pixels[i].GetB() / 255;
			result = (1 - ((1 - num1) * (1 - num2))) * 255 + 0.5f;
		}
		
		newPixel.SetB((unsigned char)result);

		num1 = (float)top.pixels[i].GetG();
		if (num1 == 0)
		{
			result = (float)bottom.pixels[i].GetG();
		}
		else if (num1 == 255)
		{
			result = 255;
		}
		else
		{
			num1 = (float)top.pixels[i].GetG() / 255;
			num2 = (float)bottom.pixels[i].GetG() / 255;
			result = (1 - ((1 - num1) * (1 - num2))) * 255 + 0.5f;
		}

		newPixel.SetG((unsigned char)result);

		num1 = (float)top.pixels[i].GetR();
		if (num1 == 0)
		{
			result = (float)bottom.pixels[i].GetR();
		}
		else if (num1 == 255)
		{
			result = 255;
		}
		else
		{
			num1 = (float)top.pixels[i].GetR() / 255;
			num2 = (float)bottom.pixels[i].GetR() / 255;
			result = (1 - ((1 - num1) * (1 - num2))) * 255 + 0.5f;
		}

		newPixel.SetR((unsigned char)result);

		this->pixels.push_back(newPixel);
	}
}
void Image::Overlay(Image& top, Image& bottom)
{
	for (unsigned int i = 0; i < top.pixels.size(); i++)
	{
		Pixel newPixel;
		float num1, num2, result;

		num1 = (float)top.pixels[i].GetB() / 255;
		num2 = (float)bottom.pixels[i].GetB() / 255;
		if (num2 > 0.5)
		{
			result = (1 - (2 * (1 - num1) * (1 - num2))) * 255 + 0.5f;
		}
		else if (num2 <= 0.5)
		{
			result = (2 * num1 * num2) * 255 + 0.5f;
		}

		newPixel.SetB((unsigned char)result);
		
		num1 = (float)top.pixels[i].GetG() / 255;
		num2 = (float)bottom.pixels[i].GetG() / 255;
		if (num2 > 0.5)
		{
			result = (1 - (2 * (1 - num1) * (1 - num2))) * 255 + 0.5f;
		}
		else if (num2 <= 0.5)
		{
			result = (2 * num1 * num2) * 255 + 0.5f;
		}

		newPixel.SetG((unsigned char)result);

		num1 = (float)top.pixels[i].GetR() / 255;
		num2 = (float)bottom.pixels[i].GetR() / 255;
		if (num2 > 0.5)
		{
			result = (1 - (2 * (1 - num1) * (1 - num2))) * 255 + 0.5f;
		}
		else if (num2 <= 0.5)
		{
			result = (2 * num1 * num2) * 255 + 0.5f;
		}

		newPixel.SetR((unsigned char)result);

		this->pixels.push_back(newPixel);
	}
}
void Image::AddToChannel(float num, char color)
{
	for (unsigned int i = 0; i < this->pixels.size(); i++)
	{
		this->pixels[i].Add(num, color);
	}
}
void Image::ScaleChannel(float num, char color)
{
	for (unsigned int i = 0; i < this->pixels.size(); i++)
	{
		this->pixels[i].Multiply(num, color);
	}
}
void Image::WriteBChannel()
{
	for (unsigned int i = 0; i < this->pixels.size(); i++)
	{
		this->pixels[i].SetR(this->pixels[i].GetB());
		this->pixels[i].SetG(this->pixels[i].GetB());
	}
}
void Image::WriteGChannel()
{
	for (unsigned int i = 0; i < this->pixels.size(); i++)
	{
		this->pixels[i].SetR(this->pixels[i].GetG());
		this->pixels[i].SetB(this->pixels[i].GetG());
	}
}
void Image::WriteRChannel()
{
	for (unsigned int i = 0; i < this->pixels.size(); i++)
	{
		this->pixels[i].SetB(this->pixels[i].GetR());
		this->pixels[i].SetG(this->pixels[i].GetR());
	}
}
void Image::Combine(Image& red, Image& green, Image& blue)
{
	for (unsigned int i = 0; i < red.pixels.size(); i++)
	{
		Pixel newPixel;
		newPixel.SetR(red.pixels[i].GetR());
		newPixel.SetG(green.pixels[i].GetG());
		newPixel.SetB(blue.pixels[i].GetB());
		this->pixels.push_back(newPixel);
	}
}
void Image::Check(Image& img)
{
	for (unsigned int i = 0; i < img.pixels.size(); i++)
	{
		unsigned char blue1, blue2, green1, green2, red1, red2;
		blue1 = this->pixels[i].GetB();
		blue2 = img.pixels[i].GetB();
		green1 = this->pixels[i].GetG();
		green2 = img.pixels[i].GetG();
		red1 = this->pixels[i].GetR();
		red2 = img.pixels[i].GetR();
		if (blue1 != blue2 || green1 != green2 || red1 != red2)
		{
			cout << "While checking, found an error." << endl;
		}
	}
	cout << "Done checking." << endl;
} 
void Image::MakeBigImage(Image& img1, Image& img2, Image& img3, Image& img4)
{
	unsigned int rowCounter = 0, img1Counter = 0, img2Counter = 0;

	while (rowCounter < 512)
	{
		for (unsigned int i = 0; i < 512; i++)
		{
			Pixel newPixel;
			newPixel.SetB(img1.pixels[img1Counter].GetB());
			newPixel.SetG(img1.pixels[img1Counter].GetG());
			newPixel.SetR(img1.pixels[img1Counter].GetR());
			this->pixels.push_back(newPixel);
			img1Counter++;
		}

		for (unsigned int i = 0; i < 512; i++)
		{
			Pixel newPixel;
			newPixel.SetB(img2.pixels[img2Counter].GetB());
			newPixel.SetG(img2.pixels[img2Counter].GetG());
			newPixel.SetR(img2.pixels[img2Counter].GetR());
			this->pixels.push_back(newPixel);
			img2Counter++;
		}
	
		rowCounter++;
	}

	rowCounter = 0;
	img1Counter = 0;
	img2Counter = 0;

	while (rowCounter < 512)
	{
		for (unsigned int i = 0; i < 512; i++)
		{
			Pixel newPixel;
			newPixel.SetB(img3.pixels[img1Counter].GetB());
			newPixel.SetG(img3.pixels[img1Counter].GetG());
			newPixel.SetR(img3.pixels[img1Counter].GetR());
			this->pixels.push_back(newPixel);
			img1Counter++;
		}

		for (unsigned int i = 0; i < 512; i++)
		{
			Pixel newPixel;
			newPixel.SetB(img4.pixels[img2Counter].GetB());
			newPixel.SetG(img4.pixels[img2Counter].GetG());
			newPixel.SetR(img4.pixels[img2Counter].GetR());
			this->pixels.push_back(newPixel);
			img2Counter++;
		}

		rowCounter++;
	}
}