#include "Header.h"
#include<iostream>
#include <fstream>
using namespace std;

Header::Header() {
	idLength = 0;
	colorMapType = 0;
	imageType = 2;
	colorMapOrigin = 0;
	colorMapLength = 0;
	colorMapDepth = 0;
	xOrigin = 0;
	yOrigin = 0;
	imageWidth = 0;
	imageHeight = 0;
	bitsPerPixel = 24;
	imageDescriptor = 0;
}

Header::Header(short& inputWidth, short& inputHeight) {
	idLength = 0;
	colorMapType = 0;
	imageType = 2;
	colorMapOrigin = 0;
	colorMapLength = 0;
	colorMapDepth = 0;
	xOrigin = 0;
	yOrigin = 0;
	imageWidth = inputWidth;
	imageHeight = inputHeight;
	bitsPerPixel = 24;
	imageDescriptor = 0;
}

void Header::PrintHeader() {
	cout << "ID length: " << (int)idLength << endl;
	cout << "Color map type: " << (int)colorMapType << endl;
	cout << "Image type: " << (int)imageType << endl;
	cout << "Color map origin: " << colorMapOrigin << endl;
	cout << "Color map length: " << colorMapLength << endl;
	cout << "Color map depth: " << (int)colorMapDepth << endl;
	cout << "x origin: " << xOrigin << endl;
	cout << "y origin: " << yOrigin << endl;
	cout << "Image width: " << imageWidth << endl;
	cout << "Image height: " << imageHeight << endl;
	cout << "Bits per pixel: " << (int)bitsPerPixel << endl;
	cout << "Image descriptor: " << (int)imageDescriptor << endl;
}