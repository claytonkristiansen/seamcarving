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
	Pixel** image = new Pixel * [width];

	bool fail = false;

	for (int i = 0; i < width; ++i) { // loop through each column
	  // assign that column to a one dimensional array on the heap of Pixels
	  //  that has height elements (i.e. the number of rows)
		image[i] = new Pixel[height];

		if (image[i] == nullptr) { // failed to allocate
			fail = true;
		}
	}

	if (fail) { // if any allocation fails, clean up and avoid memory leak
	  // deallocate any arrays created in for loop
		for (int i = 0; i < width; ++i) {
			delete[] image[i]; // deleting nullptr is not a problem
		}
		delete[] image; // dlete array of pointers
		return nullptr;
	}

	// initialize cells
	//cout << "Initializing cells..." << endl;
	for (int row = 0; row < height; ++row) {
		for (int col = 0; col < width; ++col) {
			//cout << "(" << col << ", " << row << ")" << endl;
			image[col][row] = { 0, 0, 0 };
		}
	}
	cout << "End createImage... " << endl;
	return image;
}

void deleteImage(Pixel** image, int width/*, int height*/) {
	cout << "Start deleteImage..." << endl;
	// avoid memory leak by deleting the array
	for (int i = 0; i < width; ++i) {
		delete[] image[i]; // delete each individual array placed on the heap
	}
	delete[] image;
	image = nullptr;
}

int* createSeam(int length) 
{
	int* arr = new int[length];
	for (int i = 0; i < length; ++i)
	{
		arr[i] = 0;
	}
	return arr;
}

void deleteSeam(int* seam) 
{
	delete[] seam;
}

bool loadImage(const std::string filename, Pixel** image, int width, int height) {
	//cout << "Loading image..." << endl;
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
	if ((toupper(type[0]) != 'P') || (type[1] != '3')) { // check that type is correct
		cout << "Error: type is " << type << " instead of P3" << endl;
		return false;
	}
	if (ifs.fail())
	{
		cout << "Error: read non-integer value" << endl;
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
		cout << "Error: input width (" << width << ") does not match value in file (" << w << ")" << endl;
		/*cout << "Error: file width does not match input" << endl;
		cout << " - input width: " << width << endl;
		cout << " -  file width: " << w << endl;*/
		return false;
	}
	if (h != height) { // check that height matches what was passed into the function
		cout << "Error: input height (" << height << ") does not match value in file (" << h << ")" << endl;
		/*cout << "Error: file height does not match input" << endl;
		cout << " - input height: " << height << endl;
		cout << " -  file height: " << h << endl;*/
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
	//int numPix = 0;

	// get RGB pixel values
	while (!ifs.eof())
	{
		int r, g, b = 0;
		string rTemp = "";
		ifs >> rTemp;
		if (rTemp == "" && ifs.eof())
		{
			return true;
		}
		if (row >= height)
		{
			//bool test = ifs.eof();
			cout << "Error: too many color values" << endl;
			return false;
		}
		r = std::stoi(rTemp);
		ifs >> g;
		ifs >> b;
		image[column][row].r = r;
		image[column][row].g = g;
		image[column][row].b = b;
		if (ifs.fail())
		{
			if (ifs.eof())
			{
				cout << "Error: not enough color values" << endl;
				return false;
			}
			else
			{
				cout << "Error: read non-integer value" << endl;
				return false;
			}
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
		++column;
		if (column == w)
		{
			//if (row == 124)
			//{
			//	int i = 0;
			//}
			column = 0;
			++row;
		}
	}

	return true;
}

bool outputImage(string filename, Pixel** image, int width, int height)
{
	//cout << "Outputting image..." << endl;
	// declare/define and open output file stream
	ofstream fOut(filename);


	// check if output stream opened successfully
	if (!fOut.is_open())
	{
		cout << "Error: failed to open output file " << filename << endl;
		return false;
	}

	// output preamble
	fOut << "P3\n" << width << " " << height << "\n" << 255 << "\n";

	// output pixels
	for (int i = 0; i < height; ++i)
	{
		for (int k = 0; k < width; ++k)
		{
			fOut << image[k][i].r << " " << image[k][i].g << " " << image[k][i].b << " ";
		}
		fOut << "\n";
	}
	return true;
}

int energy(Pixel** image, int x, int y, int width, int height)
{
	int sqrxg = -1;		//Square of the x gradient
	int sqryg = -1;		//Square of the y gradient
	int rDiff = 0;		//Red gradient
	int gDiff = 0;		//Green gradient
	int bDiff = 0;		//Blue gradient
	if (x > 0 && x < width - 1)	//If not an edge case for columns
	{
		rDiff = abs(image[x - 1][y].r - image[x + 1][y].r);
		gDiff = abs(image[x - 1][y].g - image[x + 1][y].g);
		bDiff = abs(image[x - 1][y].b - image[x + 1][y].b);
		sqrxg = rDiff * rDiff + gDiff * gDiff + bDiff * bDiff;
	}
	else if (x <= 0) //If column is leftmost
	{
		rDiff = abs(image[width - 1][y].r - image[x + 1][y].r);
		gDiff = abs(image[width - 1][y].g - image[x + 1][y].g);
		bDiff = abs(image[width - 1][y].b - image[x + 1][y].b);
		sqrxg = rDiff * rDiff + gDiff * gDiff + bDiff * bDiff;
	}
	else if (x >= width - 1) //If column is rightmost
	{
		rDiff = abs(image[x - 1][y].r - image[0][y].r);
		gDiff = abs(image[x - 1][y].g - image[0][y].g);
		bDiff = abs(image[x - 1][y].b - image[0][y].b);
		sqrxg = rDiff * rDiff + gDiff * gDiff + bDiff * bDiff;
	}

	if (y > 0 && y < height - 1)	//If not an edge case for rows
	{
		rDiff = abs(image[x][y - 1].r - image[x][y + 1].r);
		gDiff = abs(image[x][y - 1].g - image[x][y + 1].g);
		bDiff = abs(image[x][y - 1].b - image[x][y + 1].b);
		sqryg = rDiff * rDiff + gDiff * gDiff + bDiff * bDiff;
	}
	else if (y <= 0) //If row is topmost
	{
		rDiff = abs(image[x][height - 1].r - image[x][y + 1].r);
		gDiff = abs(image[x][height - 1].g - image[x][y + 1].g);
		bDiff = abs(image[x][height - 1].b - image[x][y + 1].b);
		sqryg = rDiff * rDiff + gDiff * gDiff + bDiff * bDiff;
	}
	else if (y >= height - 1) //If row is bottommost
	{
		rDiff = abs(image[x][y - 1].r - image[x][0].r);
		gDiff = abs(image[x][y - 1].g - image[x][0].g);
		bDiff = abs(image[x][y - 1].b - image[x][0].b);
		sqryg = rDiff * rDiff + gDiff * gDiff + bDiff * bDiff;
	}
	return sqrxg + sqryg;
}


int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam) 
{
	int curCol = start_col;
	int totalEn = energy(image, curCol, 0, width, height);;
	seam[0] = start_col;
	for (int row = 1; row < height; ++row)
	{
		int minColumn = curCol;
		int minEnergy = energy(image, curCol, row, width, height);
		if (curCol < width - 1)
		{
			int en = energy(image, curCol + 1, row, width, height);
			if (curCol < width - 1 && en < minEnergy)
			{
				minEnergy = en;
				minColumn = curCol + 1;
			}
		}
		if (curCol > 0)
		{
			int en = energy(image, curCol - 1, row, width, height);
			if (curCol > 0 && en < minEnergy)
			{
				minEnergy = en;
				minColumn = curCol - 1;
			}
		}
		totalEn += minEnergy;
		seam[row] = minColumn;
		curCol = minColumn;

	}
	return totalEn;
}

int VertSeamFast(Pixel** image, int start_col, int width, int height)
{
	int curCol = start_col;
	int totalEn = energy(image, curCol, 0, width, height);;
	for (int row = 1; row < height; ++row)
	{
		int minColumn = curCol;
		int minEnergy = energy(image, curCol, row, width, height);
		if (curCol < width - 1)
		{
			int en = energy(image, curCol + 1, row, width, height);
			if (curCol < width - 1 && en < minEnergy)
			{
				minEnergy = en;
				minColumn = curCol + 1;
			}
		}
		if (curCol > 0)
		{
			int en = energy(image, curCol - 1, row, width, height);
			if (curCol > 0 && en < minEnergy)
			{
				minEnergy = en;
				minColumn = curCol - 1;
			}
		}
		totalEn += minEnergy;
		curCol = minColumn;

	}
	return totalEn;
}



int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam) 
{
	int curRow = start_row;
	int totalEn = energy(image, 0, curRow, width, height);;
	seam[0] = start_row;
	for (int col = 1; col < width; ++col)
	{
		int minRow = curRow;
		int minEnergy = energy(image, col, curRow, width, height);
		if (curRow > 0)
		{
			int en = energy(image, col, curRow - 1, width, height);
			if (curRow > 0 && en < minEnergy)
			{
				minEnergy = en;
				minRow = curRow - 1;
			}
		}
		if (curRow < height - 1)
		{
			int en = energy(image, col, curRow + 1, width, height);
			if (curRow < height - 1 && en < minEnergy)
			{
				minEnergy = en;
				minRow = curRow + 1;
			}
		}
		totalEn += minEnergy;
		seam[col] = minRow;
		curRow = minRow;

	}
	return totalEn;
}


int* findMinVerticalSeam(Pixel** image, int width, int height) 
{
	int* seam = new int[height];
	int seamCol = 0;
	int minSeamEnergy = loadVerticalSeam(image, 0, width, height, seam);
	for (int col = 1; col < width; ++col)
	{
		int en = loadVerticalSeam(image, col, width, height, seam);
		if (en < minSeamEnergy)
		{
			minSeamEnergy = en;
			seamCol = col;
			//seam = tempSeam;
		}
	}
	loadVerticalSeam(image, seamCol, width, height, seam);
	return seam;
}

int* findMinHorizontalSeam(Pixel** image, int width, int height) 
{
	int* seam = new int[width];
	int seamRow = 0;
	int minSeamEnergy = loadHorizontalSeam(image, 0, width, height, seam);
	for (int row = 1; row < height; ++row)
	{
		int en = loadHorizontalSeam(image, row, width, height, seam);
		if (en < minSeamEnergy)
		{
			minSeamEnergy = en;
			seamRow = row;
			//seam = tempSeam;
		}
	}
	loadHorizontalSeam(image, seamRow, width, height, seam);
	return seam;
}

int find(const int A[], const size_t len, const int key)
{
	for (size_t i = 0; i < len; ++i)
	{
		if (A[i] == key)
		{
			return i;
		}
	}
	return -1;
}

void remove(Pixel A[], int len, const int idx, const int cnt)
{
	if (idx + cnt > len)
	{
		throw(std::out_of_range("index out of range"));
	}
	if (len == cnt)
	{
		len = 0;
		return;
	}
	len = len - cnt;
	for (int i = idx; i < len; ++i)
	{
		A[i] = A[i + cnt];
	}
}

void replaceFromNextCol(Pixel** A, int width, int col, int row)
{
	if (col < width - 1)
	{
		A[col][row] = A[col + 1][row];
	}
}


void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam)
{
	for (int row = 0; row < height; ++row)
	{
		replaceFromNextCol(image, width, verticalSeam[row], row);
		for (int i = verticalSeam[row] + 1; i < width; ++i)
		{
			replaceFromNextCol(image, width, i, row);
		}
	}
}

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam) 
{
	for (int col = 0; col < width; ++col)
	{
		for (int row = horizontalSeam[col]; row < height - 1; ++row)
		{
			image[col][row] = image[col][row + 1];
		}
	}
}
