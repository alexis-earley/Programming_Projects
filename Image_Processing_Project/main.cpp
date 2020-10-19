#include "Header.h"
#include"Image.h"
#include "Pixel.h"
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

void whatToDo(Image image) { //delete later
	cout << "Pixel 0: ";
	image.getPixel(0).printPixel();
	cout << "Pixel 1: ";
	image.getPixel(1).printPixel();
	cout << "Pixel 2: ";
	image.getPixel(2).printPixel();
	cout << "Pixel 39: ";
	image.getPixel(39).printPixel();
	cout << "Pixel 1638: ";
	image.getPixel(1638).printPixel();
}


Image readImage(string fileName) {
	
	ifstream file;
	Header header;

	file.open(fileName, ios_base::binary);
	if (!file.is_open()) {
		cout << "File" << fileName << "could not be opened" << endl;
		throw exception();
	}

	file.read(&header.idLength, sizeof(header.idLength));
	file.read(&header.colorMapType, sizeof(header.colorMapType));
	file.read(&header.imageType, sizeof(header.imageType));
	file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
	file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
	file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
	file.read((char*)&header.imageWidth, sizeof(header.imageWidth));
	file.read((char*)&header.imageHeight, sizeof(header.imageHeight));
	file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

	Image image(header);
	short imageHeight = image.getHeight();
	short imageWidth = image.getWidth();
	int numPixels = imageHeight * imageWidth;

	for (int i = 0; i < numPixels; i++) {
		unsigned char blue;
		unsigned char green;
		unsigned char red;
		file.read((char *)&blue, sizeof(blue));
		file.read((char*)&green, sizeof(green));
		file.read((char*)&red, sizeof(red));

		image.changePixColors(i, blue, green, red);
	}

	file.close();
	return image;
}

void writeImage(string fileName, Image image) {

	ofstream file;
	file.open(fileName, ios_base::binary);

	if (!file.is_open()) {
		cout << "File" << fileName << "could not be opened" << endl;
		throw exception(); //FIXME
	}

	Header header = image.getHeader();

	file.write(&header.idLength, sizeof(header.idLength));
	file.write(&header.colorMapType, sizeof(header.colorMapType));
	file.write(&header.imageType, sizeof(header.imageType));
	file.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	file.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	file.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	file.write((char*)&header.xOrigin, sizeof(header.xOrigin));
	file.write((char*)&header.yOrigin, sizeof(header.yOrigin));
	file.write((char*)&header.imageWidth, sizeof(header.imageWidth));
	file.write((char*)&header.imageHeight, sizeof(header.imageHeight));
	file.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	file.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	vector<Pixel> pixelVector = image.getPixelVector();
	 
	for (unsigned int i = 0; i < pixelVector.size(); i++) {
		unsigned char blue = pixelVector[i].getBlue();
		unsigned char green = pixelVector[i].getGreen();
		unsigned char red = pixelVector[i].getRed();
		file.write((char*)&blue, sizeof(blue));
		file.write((char*)&green, sizeof(green));
		file.write((char*)&red, sizeof(red));

		Pixel pixel(blue, green, red);
		image.addPixel(pixel);
	}
}

bool sameImages(Image image1, Image image2) {
	Header header1 = image1.getHeader();
	Header header2 = image2.getHeader();

	if (header1.idLength != header2.idLength) {
		return false;
	}
	if (header1.colorMapType != header2.colorMapType) {
		return false;
	}
	if (header1.imageType != header2.imageType) {
		return false;
	}
	if (header1.colorMapOrigin != header2.colorMapOrigin) {
		return false;
	}
	if (header1.colorMapLength != header2.colorMapLength) {
		return false;
	}
	if (header1.colorMapDepth != header2.colorMapDepth) {
		return false;
	}
	if (header1.xOrigin != header2.xOrigin) {
		return false;
	}
	if (header1.yOrigin != header2.yOrigin) {
		return false;
	}
	if (header1.imageWidth != header2.imageWidth) {
		return false;
	}
	if (header1.imageHeight != header2.imageHeight) {
		return false;
	}
	if (header1.bitsPerPixel != header2.bitsPerPixel) {
		return false;
	}
	if (header1.imageDescriptor != header2.imageDescriptor) {
		return false;
	}

	if ((image1.getWidth() != image2.getWidth()) || (image1.getHeight() != image2.getHeight())) {
		return false;
	}

	if (image1.getCurrentSize() != image2.getCurrentSize()) {
		return false;
	}

	vector<Pixel> image1Pixels = image1.getPixelVector();
	vector<Pixel> image2Pixels = image2.getPixelVector();

	for (unsigned int i = 0; i < image1Pixels.size(); i++) {
		Pixel pixel1 = image1Pixels[i];
		Pixel pixel2 = image2Pixels[i];
		bool samePixels = (pixel1.getBlue() == pixel2.getBlue()) && (pixel1.getGreen() == pixel2.getGreen()) && (pixel1.getRed() == pixel2.getRed());
		if (!(samePixels)) {
			return false;
		}
	}
	return true;
}

Image newImage(string fileName, short imageWidth, short imageHeight, char blue = 0, char green = 0, char red = 0) { //delete?
	Header header;
	header.imageWidth = imageWidth;
	header.imageHeight = imageHeight;
	header.imageType = 2; // typical value
	header.bitsPerPixel = 24; // typical value
	Image newImage(header);

	unsigned int imageSize = newImage.getDesiredSize();
	Pixel pixel;
	for (unsigned int i = 0; i < newImage.getDesiredSize(); i++) {
		pixel.setColors(blue, green, red);
		newImage.changePixColors(i, blue, green, red);
	}
	return newImage;
}

int roundFloat(float inputFloat) {
	return (int)(inputFloat + 0.5f);
}

int multiplyColors(unsigned char color1, unsigned char color2) {
	float multiple = (float)(((int)color1 * (int)color2) / 255.0f);
	int result = roundFloat(multiple);
	return result;
}


int multiplyColor(unsigned char color, float factor) {
	float multiple = (float)((int)color * factor);
	int result = roundFloat(multiple);
	if (result > 255) {
		result = 255;
	}
	return result;
}

int subtractColors(unsigned char color1, unsigned char color2) {
	int intColor1 = (int)color1;
	int intColor2 = (int)color2;
	int result = color2 - color1;
	if (result < 0) {
		result = 0;
	}
	return result;
}

Image multiplyImages(Image topLayer, Image bottomLayer) {
	short width = topLayer.getWidth();
	short height = topLayer.getHeight(); // top and bottom layers should have the same dimensions
	Image image(width, height);

	for (int i = 0; i < (width * height); i++) {
		int blue = multiplyColors(topLayer.getPixel(i).getBlue(), bottomLayer.getPixel(i).getBlue());
		int green = multiplyColors(topLayer.getPixel(i).getGreen(), bottomLayer.getPixel(i).getGreen());
		int red = multiplyColors(topLayer.getPixel(i).getRed(), bottomLayer.getPixel(i).getRed());
		image.changePixColors(i, blue, green, red);
	}

	return image;
}

Image multiplyImage(Image oldImage, float blueFactor, float greenFactor, float redFactor) {
	short width = oldImage.getWidth();
	short height = oldImage.getHeight(); // top and bottom layers should have the same dimensions
	Image image(width, height);

	for (int i = 0; i < (width * height); i++) {
		int blue = multiplyColor(oldImage.getPixel(i).getBlue(), blueFactor);
		int green = multiplyColor(oldImage.getPixel(i).getGreen(), greenFactor);
		int red = multiplyColor(oldImage.getPixel(i).getRed(), redFactor);
		image.changePixColors(i, blue, green, red);
	}

	return image;
}

Image subtractImages(Image topLayer, Image bottomLayer) {
	short width = topLayer.getWidth();
	short height = topLayer.getHeight(); // top and bottom layers should have the same dimensions
	Image image(width, height);

	for (int i = 0; i < (width * height); i++) {
		int blue = subtractColors(topLayer.getPixel(i).getBlue(), bottomLayer.getPixel(i).getBlue());
		int green = subtractColors(topLayer.getPixel(i).getGreen(), bottomLayer.getPixel(i).getGreen());
		int red = subtractColors(topLayer.getPixel(i).getRed(), bottomLayer.getPixel(i).getRed());
		image.changePixColors(i, blue, green, red);
	}

	return image;
}

Image screenImages(Image topLayer, Image bottomLayer) {
	short width = topLayer.getWidth();
	short height = topLayer.getHeight();
	unsigned const char value = 255;
	Image fullColor(width, height, value, value, value);
	Image result = subtractImages((multiplyImages(subtractImages(topLayer, fullColor), subtractImages(bottomLayer, fullColor))), fullColor);
	return result;
}

void testResult(string testNum, Image result) {
	cout << testNum << ": ";

	Image otherImage = readImage("examples//EXAMPLE_" + testNum + ".tga");

	if (sameImages(result, otherImage)) {
		cout << "Passed" << endl;
	}
	else {
		cout << "Failed" << endl;
	}
}

Image combineChannels(Image blueLayer, Image greenLayer, Image redLayer) {

	short width = blueLayer.getWidth();
	short height = blueLayer.getHeight();
	Image result(width, height);

	for (int i = 0; i < (width * height); i++) {

		result.changePixColors(i, blueLayer.getPixel(i).getBlue(), greenLayer.getPixel(i).getGreen(), redLayer.getPixel(i).getRed());
	}
	return result;
}

unsigned char overlayColor(unsigned char color1, unsigned char color2) {
	int newColor1 = (int)color1;
	int newColor2 = (int)color2;
	unsigned char color;
	if (newColor2 > 127.5f) {
		color = 255 - roundFloat(2.0f * (float)(((int)(255 - newColor1) * (int)(255 - newColor2)) / 255.0f));
	}
	else {
		color = roundFloat((float)(2.0f * (float)(((int)(newColor1) * (int)(newColor2)) / 255.0f)));
	}
	if (color > 255) {
		color = 255;
	}
	return color;
}

Pixel overlayPixel(Pixel pixel1, Pixel pixel2) {
	Pixel pixel;
	unsigned char newBlue = overlayColor(pixel1.getBlue(), pixel2.getBlue());
	pixel.setBlue(newBlue);
	unsigned char newGreen = overlayColor(pixel1.getGreen(), pixel2.getGreen());
	pixel.setGreen(newGreen);
	unsigned char newRed = overlayColor(pixel1.getRed(), pixel2.getRed());
	pixel.setRed(newRed);
	return pixel;
}

Image overlay(Image topLayer, Image bottomLayer) {
	short width = topLayer.getWidth();
	short height = topLayer.getHeight(); 
	Image result(width, height);
	
	Pixel pixel;
	for (int i = 0; i < (width * height); i++) {
		pixel = overlayPixel(topLayer.getPixel(i), bottomLayer.getPixel(i));
		result.changePixel(i, pixel);
	}

	return result;
}

Image addQuad(Image image, Image output, short width, short height, short width1, short height1, short width2, bool bottom = true, bool left = true) {
	vector<Pixel> pixelVector = image.getPixelVector();
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			int oldIndex = (row * width1) + col;
			Pixel pixel = pixelVector[oldIndex];
			char blue = pixel.getBlue();
			char green = pixel.getGreen();
			char red = pixel.getRed();

			short extraWidth = 0;
			short extraHeight = 0;
			if (!left) {
				extraWidth = width1;
			}
			if (!bottom) {
				extraHeight = height1;
			}

			int newIndex = ((row + extraHeight) * (width1 + width2)) + col + extraWidth;
			output.changePixColors(newIndex, blue, green, red);
		}
	}
	return output;
}

void test1() {
	Image topLayer = readImage("input//layer1.tga");
	Image bottomLayer = readImage("input//pattern1.tga");
	Image result = multiplyImages(topLayer, bottomLayer);
	writeImage("output//part1.tga", result);
	testResult("part1", result);
}


void test2() {
	Image topLayer = readImage("input//layer2.tga");
	Image bottomLayer = readImage("input//car.tga");
	Image result = subtractImages(topLayer, bottomLayer);
	writeImage("output//part2.tga", result);

	testResult("part2", result);
}

void test3() {
	Image topLayer = readImage("input//layer1.tga");
	Image bottomLayer = readImage("input//pattern2.tga");
	Image tempResult = multiplyImages(topLayer, bottomLayer);
	writeImage("output//testing.tga", tempResult);
	Image newTopLayer = readImage("input//text.tga");
	Image result = screenImages(newTopLayer, tempResult);
	writeImage("output//part3.tga", result);

	testResult("part3", result);
}

void test4() {
	Image topLayer = readImage("input//layer2.tga");
	Image bottomLayer = readImage("input//circles.tga");
	Image tempResult = multiplyImages(topLayer, bottomLayer);
	Image newTopLayer = readImage("input//pattern2.tga");
	Image result = subtractImages(newTopLayer, tempResult);
	writeImage("output//part4.tga", result);

	testResult("part4", result);
}

void test5() {
	Image topLayer = readImage("input//layer1.tga");
	Image bottomLayer = readImage("input//pattern1.tga");
	Image result = overlay(topLayer, bottomLayer);
	writeImage("output//part5.tga", result);

	testResult("part5", result);
}

void test6() {
	Image car = readImage("input//car.tga");
	for (unsigned int i = 0; i < car.getCurrentSize(); i++) {
		car.addGreen(i, 200);
	}
	writeImage("output//part6.tga", car);
	
	testResult("part6", car);
}

void test7() {
	Image car = readImage("input//car.tga");
	Image result = multiplyImage(car, 0.0f, 1.0f, 4.0f);
	writeImage("output//part7.tga", result);

	testResult("part7", result);
}

void test8() {
	Image car = readImage("input//car.tga");
	short width = car.getWidth();
	short height = car.getHeight();
	Image result1(width, height);
	Image result2(width, height);
	Image result3(width, height);

	vector<Pixel> pixelVector = car.getPixelVector();
	unsigned char blue;
	unsigned char green;
	unsigned char red;

	for (unsigned int i = 0; i < pixelVector.size(); i++) {
		blue = pixelVector[i].getBlue();
		green = pixelVector[i].getGreen();
		red = pixelVector[i].getRed();

		result1.changePixColors(i, blue, blue, blue);
		result2.changePixColors(i, green, green, green);
		result3.changePixColors(i, red, red, red);
	}

	writeImage("output//part8_b.tga", result1);
	writeImage("output//part8_g.tga", result2);
	writeImage("output//part8_r.tga", result3);

	testResult("part8_b", result1);
	testResult("part8_g", result2);
	testResult("part8_r", result3);
}

void test9() {
	Image blueLayer = readImage("input//layer_blue.tga");
	Image greenLayer = readImage("input//layer_green.tga");
	Image redLayer = readImage("input//layer_red.tga");
	Image result = combineChannels(blueLayer, greenLayer, redLayer);

	writeImage("output//part9.tga", result);

	testResult("part9", result);
}

void test10() {
	Image textImage = readImage("input//text2.tga");

	int size = textImage.getCurrentSize();
	for (int i = 0; i < (int)(size / 2); i++) {
		int oppIndex = size - i - 1;
		textImage.swapPixels(i, oppIndex);
	}

	writeImage("output//part10.tga", textImage);

	testResult("part10", textImage);
}

void EC() {
	Image bottomLeft = readImage("input//text.tga");
	Image bottomRight = readImage("input//pattern1.tga");
	Image topLeft = readImage("input//car.tga");
	vector<Pixel> pixelVector = topLeft.getPixelVector();
	Image topRight = readImage("input//circles.tga");

	int width1 = bottomLeft.getWidth();
	int height1 = bottomLeft.getHeight();
	int width2 = bottomRight.getWidth();
	int height2 = bottomRight.getHeight();
	int width3 = topLeft.getWidth();
	int height3 = topLeft.getHeight();
	int width4 = topRight.getWidth();
	int height4 = topRight.getHeight();

	short outputWidth = width1 + width2;
	short outputHeight = height1 + height3;
	Image result(outputWidth, outputHeight);

	result = addQuad(bottomLeft, result, width1, height1, width1, height1, width2, true, true);
	result = addQuad(bottomRight, result, width2, height2, width1, height1, width2, true, false);
	result = addQuad(topLeft, result, width3, height3, width1, height1, width2, false, true);
	result = addQuad(topRight, result, width4, width4, width1, height1, width2, false, false);

	writeImage("output//extracredit.tga", result);

	testResult("extracredit", result);
}

int main()
{
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
	test7();
	test8();
	test9();
	test10();
	EC();

	return 0;
}