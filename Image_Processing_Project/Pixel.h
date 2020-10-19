#pragma once

#include<iostream>
using namespace std;

class Pixel
{
private:
	unsigned char blue;
	unsigned char green;
	unsigned char red;
public:
	Pixel();
	Pixel(unsigned char& blueInput, unsigned char& greenInput, unsigned char& redInput);
	void setColors(const unsigned char& blueInput, const unsigned char& greenInput, const unsigned char& redInput);
	void setBlue(unsigned char& blueInput);
	void setGreen(unsigned char& greenInput);
	void addGreen(const unsigned int& greenInput);
	void setRed(unsigned char& redInput);
	string getColors();
	unsigned char getBlue();
	unsigned char getGreen();
	unsigned char getRed();
	void printPixel();
};

