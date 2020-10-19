#include "Image.h"

Image::Image() {
	Header newHeader;
	header = newHeader;
	width = 0;
	height = 0;
	pixelVector = {};
}

Image::Image(short& inputWidth, short& inputHeight, const char& blueInput, const char& greenInput, const char& redInput) {
	Header newHeader(inputWidth, inputHeight);
	header = newHeader;
	width = inputWidth;
	height = inputHeight;
	pixelVector = {};
	Pixel pixel;
	for (int i = 0; i < (inputWidth * inputHeight); i++) {
		pixel.setColors(blueInput, greenInput, redInput);
		pixelVector.push_back(pixel);
	}
}

Image::Image(Header& inputHeader, const char& blueInput, const char& greenInput, const char& redInput) {
	header = inputHeader;
	width = header.imageWidth;
	height = header.imageHeight;
	pixelVector = {};
	Pixel pixel;
	int width = header.imageWidth;
	int height = header.imageHeight;
	for (int i = 0; i < (width * height); i++) {
		pixel.setColors(blueInput, greenInput, redInput);
		pixelVector.push_back(pixel);
	}
}

void Image::setHeader(Header& inputHeader) {
	header = inputHeader;
	width = header.imageWidth;
	height = header.imageHeight;
}

Header Image::getHeader() {
	return header;
}

Pixel Image::getPixel(const int& index) {
	return pixelVector[index];
}

vector<Pixel> Image::getPixelVector() {
	return pixelVector;
}

short Image::getWidth() {
	return width;
}


short Image::getHeight() {
	return height;
}

void Image::addPixel(Pixel& pixel) {
	pixelVector.push_back(pixel);
}

void Image::changePixel(int& index, Pixel& pixel) {
	pixelVector[index] = pixel;
}

Pixel Image::locatePixel(short& row, short& column) {
	int flippedRow = height - row - 1; //gives row from bottom, not top
	int num = (flippedRow * width) + column;
	return pixelVector[num];
}

void Image::changePixColors(const int& index, const unsigned char& blueInput, const unsigned char& greenInput, const unsigned char& redInput) {
	pixelVector[index].setColors(blueInput, greenInput, redInput);
}

void Image::changeBlue(int& index, unsigned char& blueInput) {
	pixelVector[index].setBlue(blueInput);
}
void Image::changeGreen(int& index, unsigned char& greenInput) {
	pixelVector[index].setGreen(greenInput);
}

void Image::changeRed(int& index, unsigned char& redInput) {
	pixelVector[index].setRed(redInput);
}

void Image::addGreen(const int& index, const unsigned int& greenInput) {
	pixelVector[index].addGreen(greenInput);
}

unsigned int Image::getCurrentSize() {
	return pixelVector.size();
}

unsigned int Image::getDesiredSize() {
	return width * height;
}

void Image::swapPixels(int& index1, int& index2) {
	Pixel pixel1 = pixelVector[index1];
	Pixel pixel2 = pixelVector[index2];
	Pixel temp = pixel2;
	pixelVector[index2] = pixel1;
	pixelVector[index1] = temp;
}    