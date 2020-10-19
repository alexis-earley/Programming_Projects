#include "Pixel.h"
#include<iostream>
using namespace std;

Pixel::Pixel() {
	blue = 0;
	green = 0;
	red = 0;
}

Pixel::Pixel(unsigned char& blueInput, unsigned char& greenInput, unsigned char& redInput) {
	blue = blueInput;
	green = greenInput;
	red = redInput;
}

void Pixel::setColors(const unsigned char& blueInput, const unsigned char& greenInput, const unsigned char& redInput) {
	blue = blueInput;
	green = greenInput;
	red = redInput;
}

void Pixel::setBlue(unsigned char& blueInput) {
	blue = blueInput;
}

void Pixel::setGreen(unsigned char& greenInput) {
	green = greenInput;
}

void Pixel::setRed(unsigned char& redInput) {
	red = redInput;
}

void Pixel::addGreen(const unsigned int& greenInput) { //FIXME
	int intVersion = (int)green;
	intVersion += greenInput;
	if (intVersion >= 255) {
		intVersion = 255;
	}
	
	green = intVersion;
}

string Pixel::getColors() {
	string outputString = "";
	outputString += blue;
	outputString += green;
	outputString += red;
	return outputString;
}

unsigned char Pixel::getBlue() {
	return blue;
}

unsigned char Pixel::getGreen() {
	return green;
}

unsigned char Pixel::getRed() {
	return red;
}

void Pixel::printPixel() {
	cout << "Blue: " << (int)blue << endl;
	cout << "Green: " << (int)green << endl;
	cout << "Red: " << (int)red << endl;
}