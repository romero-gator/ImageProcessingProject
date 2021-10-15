#include <iostream>
#include <fstream>
#include <string>
#include "Image.h"
#include "Pixel.h"
using namespace std;

void InputFile(Image& img, string filename)
{
	ifstream inFile(filename, ios_base::binary);
	if (inFile.is_open())
	{
		img.DeserializeHeader(inFile);
		img.DeserializeData(inFile);
		inFile.close();
	}
}
void OutputFile(Image& img, string filename)
{
	ofstream outFile(filename, ios_base::binary);
	if (outFile.is_open())
	{
		img.SerializeHeader(outFile);
		img.SerializeData(outFile);
		outFile.close();
	}
}

void TestPart1()
{
	Image img1;
	InputFile(img1, "input/layer1.tga");

	Image img2;
	InputFile(img2, "input/pattern1.tga");
	
	Image img3;
	img3.SetHeight(img1.GetHeight());
	img3.SetWidth(img1.GetWidth());
	img3.Multiply(img1, img2);
	OutputFile(img3, "output/part1.tga");
}
void TestPart2()
{
	Image img1;
	InputFile(img1, "input/layer2.tga");

	Image img2;
	InputFile(img2, "input/car.tga");

	Image img3;
	img3.SetHeight(img1.GetHeight());
	img3.SetWidth(img1.GetWidth());
	img3.Subtract(img1, img2);
	OutputFile(img3, "output/part2.tga");
}
void TestPart3()
{
	Image img1;
	InputFile(img1, "input/layer1.tga");

	Image img2;
	InputFile(img2, "input/pattern2.tga");

	Image img3;
	img3.SetHeight(img1.GetHeight());
	img3.SetWidth(img1.GetWidth());
	img3.Multiply(img1, img2);

	Image img4;
	InputFile(img4, "input/text.tga");

	Image img5;
	img5.SetHeight(img4.GetHeight());
	img5.SetWidth(img4.GetWidth());
	img5.Screen(img3, img4);
	OutputFile(img5, "output/part3.tga");
}
void TestPart4()
{
	Image img1;
	InputFile(img1, "input/layer2.tga");

	Image img2;
	InputFile(img2, "input/circles.tga");

	Image img3;
	img3.SetHeight(img1.GetHeight());
	img3.SetWidth(img1.GetWidth());
	img3.Multiply(img1, img2);

	Image img4;
	InputFile(img4, "input/pattern2.tga");

	Image img5;
	img5.SetHeight(img4.GetHeight());
	img5.SetWidth(img4.GetWidth());
	img5.Subtract(img4, img3);
	OutputFile(img5, "output/part4.tga");
}
void TestPart5()
{
	Image img1;
	InputFile(img1, "input/layer1.tga");

	Image img2;
	InputFile(img2, "input/pattern1.tga");
	
	Image img3;
	img3.SetHeight(img1.GetHeight());
	img3.SetWidth(img1.GetWidth());
	img3.Overlay(img1, img2);
	OutputFile(img3, "output/part5.tga");
}
void TestPart6()
{
	Image img1;
	InputFile(img1, "input/car.tga");
	img1.AddToChannel(200, 'G');
	OutputFile(img1, "output/part6.tga");
}
void TestPart7()
{
	Image img1;
	InputFile(img1, "input/car.tga");
	img1.ScaleChannel(4, 'R');
	img1.ScaleChannel(0, 'B');
	OutputFile(img1, "output/part7.tga");
}
void TestPart8()
{
	Image img1;
	InputFile(img1, "input/car.tga");
	img1.WriteBChannel();
	OutputFile(img1, "output/part8_b.tga");
	
	Image img2;
	InputFile(img2, "input/car.tga");
	img2.WriteGChannel();
	OutputFile(img2, "output/part8_g.tga");

	Image img3;
	InputFile(img3, "input/car.tga");
	img3.WriteRChannel();
	OutputFile(img3, "output/part8_r.tga");
}
void TestPart9()
{
	Image img1;
	InputFile(img1, "input/layer_red.tga");
	
	Image img2;
	InputFile(img2, "input/layer_green.tga");
	
	Image img3;
	InputFile(img3, "input/layer_blue.tga");
	
	Image img4;
	img4.SetHeight(img1.GetHeight());
	img4.SetWidth(img1.GetWidth());
	img4.Combine(img1, img2, img3);
	OutputFile(img4, "output/part9.tga");
}
void TestPart10()
{
	Image img1;
	InputFile(img1, "input/text2.tga");
	ofstream outFile1("output/part10.tga");
	if (outFile1.is_open())
	{
		img1.SerializeHeader(outFile1);
		img1.SerializeDataUpsideDown(outFile1);
		outFile1.close();
	}
}
void ExtraCredit()
{
	Image img1;
	InputFile(img1, "input/car.tga");

	Image img2;
	InputFile(img2, "input/circles.tga");

	Image img3;
	InputFile(img3, "input/text.tga");

	Image img4;
	InputFile(img4, "input/pattern1.tga");

	Image img5;
	img5.SetHeight(1024);
	img5.SetWidth(1024);
	img5.MakeBigImage(img3, img4, img1, img2);
	OutputFile(img5, "output/extracredit.tga");
}

int main()
{
	TestPart1();
	TestPart2();
	TestPart3();
	TestPart4();
	TestPart5();
	TestPart6();
	TestPart7();
	TestPart8();
	TestPart9();
	TestPart10();
	ExtraCredit();

	return 0;
}