#pragma once
#include "Header.h"
#include "Pixel.h"
#include<vector>

class Image
{
public:
	Image();
	Image(short& inputWidth, short& inputHeight, const char& blueInput = 0, const char& greenInput = 0, const char& redInput = 0);
	Image(Header& inputHeader, const char& blueInput = 0, const char& greenInput = 0, const char& redInput = 0);
	Header getHeader();
	void setHeader(Header& inputHeader);
	vector<Pixel> getPixelVector();
	Pixel getPixel(const int& index);
	short getWidth();
	short getHeight();
	unsigned int getCurrentSize();
	unsigned int getDesiredSize();
	void addPixel(Pixel& pixel);
	void changePixel(int& index, Pixel& pixel);
	Pixel locatePixel(short& row, short& column);
	void changePixColors(const int& index, const unsigned char& blueInput, const unsigned char& greenInput, const unsigned char& redInput);
	void changeBlue(int& index, unsigned char& blueInput);
	void changeGreen(int& index, unsigned char& greenInput);
	void changeRed(int& index, unsigned char& redInput);
	void addGreen(const int& index, const unsigned int& greenInput);
	void swapPixels(int& index1, int& index2);
private:
	Header header;
	vector<Pixel> pixelVector;
	short width;
	short height;
};