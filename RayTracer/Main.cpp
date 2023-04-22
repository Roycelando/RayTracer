#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include"pixel.h"
#include"vector.h"
#include"shape.h"


// function defitiion
void renderImage();
void createBackground(pixel* frameBuffer);
void printPixels(pixel* frameBuffer);

//global variables
const int width = 500;
const int height = 500;

pixel frameBuffer[width*height];

int main() {

	Shape shape;


		return 0;
}



/*
* This method fills the frame buffer with the colour of our background
*/
void createBackground(pixel* frameBuffer) {
	for (unsigned int i = 0; i < height; i++ ) {
		for (unsigned int j = 0; j < width; j++) {
			float r = i / (float)(height-1);
			float g = j / (float)(width-1);
			float b = 0.25;
			pixel p = { r,g,b};

			frameBuffer[(i * height) + j] = p;
			
		}
	}

}

void renderImage() {
	std::ofstream file("./image.ppm");
	file << "P3\n" << width << " " << height << "\n255\n";
	for (int i = 0; i < width * height; i++) {
		pixel p = frameBuffer[i];
		int r = p.r * 255.999;
		int g = p.g * 255.999;
		int b = p.b * 255.999;


		file << r << ' ' << g << ' ' << b << '\n';
	}

	
	file.close();
	
}

void printPixels(pixel* frameBuffer) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p = frameBuffer[(i * height) + j];
			std::cout << "r: " << p.r<< " g: " <<p.g << " b: " <<p.b << std::endl;
		}
		std::cout << std::endl;
	}



}