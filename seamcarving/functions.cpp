#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

Pixel** createImage(int width, int height) {
  cout << "Start createImage... " << endl;
  
  // Create a one dimensional array on the heap of pointers to Pixels 
  //    that has width elements (i.e. the number of columns)
  Pixel** image = new Pixel*[width];
  
  bool fail = false;
  
  for (int i=0; i < width; ++i) { // loop through each column
    // assign that column to a one dimensional array on the heap of Pixels
    //  that has height elements (i.e. the number of rows)
    image[i] = new Pixel[height];
    
    if (image[i] == nullptr) { // failed to allocate
      fail = true;
    }
  }
  
  if (fail) { // if any allocation fails, clean up and avoid memory leak
    // deallocate any arrays created in for loop
    for (int i=0; i < width; ++i) {
      delete [] image[i]; // deleting nullptr is not a problem
    }
    delete [] image; // dlete array of pointers
    return nullptr;
  }
  
  // initialize cells
  //cout << "Initializing cells..." << endl;
  for (int row=0; row<height; ++row) {
    for (int col=0; col<width; ++col) {
      //cout << "(" << col << ", " << row << ")" << endl;
      image[col][row] = { 0, 0, 0 };
    }
  }
  cout << "End createImage... " << endl;
  return image;
}

void deleteImage(Pixel** image, int width, int height) {
  cout << "Start deleteImage..." << endl;
  // avoid memory leak by deleting the array
  for (int i=0; i<width; ++i) {
    delete [] image[i]; // delete each individual array placed on the heap
  }
  delete [] image;
  image = nullptr;
}

int* createSeam(int length) {
  return nullptr;
}

void deleteSeam(int* seam) {
}

bool loadImage(const char filename[], Pixel** image, int width, int height) {
	cout << "Loading image..." << endl;
	// declare/define and open input file stream
	ifstream ifs(filename);

	// check if input stream opened successfully
	if (!ifs.is_open()) {
		cout << "Error: failed to open input file - " << filename << endl;
		return false;
	}

	// get type from preamble
	char type[3];
	ifs >> type; // should be P3
	if (ifs.fail())
	{
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
		cout << "Error: type is " << type << "instead of P3" << endl;
		return false;
	}

	// get width (w) and height (h) from preamble
	int w = 0, h = 0;
	ifs >> w >> h;
	if (ifs.fail())
	{
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if (w != width) { // check that width matches what was passed into the function
		cout << "Error: file width does not match input" << endl;
		cout << " - input width: " << width << endl;
		cout << " -  file width: " << w << endl;
		return false;
	}
	if (h != height) { // check that height matches what was passed into the function
		cout << "Error: file height does not match input" << endl;
		cout << " - input height: " << height << endl;
		cout << " -  file height: " << h << endl;
		return false;
	}

	// get maximum value from preamble
	int colorMax = 0;
	ifs >> colorMax;
	if (ifs.fail())
	{
		cout << "Error: read non-integer value" << endl;
		return false;
	}
	if (colorMax != 255) {
		cout << "Error: file is not using RGB color values." << endl;
		return false;
	}

	int row = 0;
	int column = 0;
	int numPix = 0;

	// get RGB pixel values
	while (!ifs.eof())
	{
		ifs >> image[column][row].r;
		ifs >> image[column][row].g;
		ifs >> image[column][row].b;
		if (ifs.fail())
		{
			cout << "Error: read non-integer value" << endl;
			return false;
		}
		if (image[column][row].r < 0 || image[column][row].r > 255)
		{
			cout << "Error: invalid color value " << image[column][row].r;
			return false;
		}
		if (image[column][row].g < 0 || image[column][row].g > 255)
		{
			cout << "Error: invalid color value " << image[column][row].g;
			return false;
		}
		if (image[column][row].b < 0 || image[column][row].b > 255)
		{
			cout << "Error: invalid color value " << image[column][row].b;
			return false;
		}
		++row;
		if (row == h)
		{
			row = 0;
			++column;
		}
	}
	if (column < width || row < height)
	{

	}

	return true;
}

bool outputImage(string filename, Pixel** image, int width, int height) {
  return true;
}

int energy(Pixel** image, int x, int y, int width, int height) { 
  return 0;
}

int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) {
  return 0;
}

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) {
  return 0;
}

int* findMinVerticalSeam(Pixel** image, int width, int height) {
  return nullptr;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) {
  return nullptr;
}

void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam) {
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) {
}
