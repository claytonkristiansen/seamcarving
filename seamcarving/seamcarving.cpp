#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;

void PrintArr(int arr[], int len)
{
	for (int i = 0; i < len; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	string filename;
	int width = 0;
	int height = 0;
	int originalWidth = 0;
	//int originalHeight = 0;
	int targetWidth = 0;
	int targetHeight = 0;
	int debugMode = 0;
	

	//Pixel** image = createImage(200, 125);

	//width = 200;
	//height = 125;

	switch (debugMode)
	{
	case 0:
	{

		cout << "Input filename: ";
		std::cin >> filename;

		// add error checking for width, height, targetWidth, and targetHeight
		cout << "Input width and height: ";
		std::cin >> width;
		if (std::cin.fail())
		{
			cout << "Error: width is a non-integer value";
			return 0;
		}
		std::cin >> height;
		if (std::cin.fail())
		{
			cout << "Error: height is a non-integer value";
			return 0;
		}
		cout << "Input target width and height: ";
		std::cin >> targetWidth;
		if (std::cin.fail())
		{
			cout << "Error: target width is a non-integer value";
			return 0;
		}
		std::cin >> targetHeight;
		if (std::cin.fail())
		{
			cout << "Error: target height is a non-integer value";
			return 0;
		}

		if (width <= 0)
		{
			cout << "Error: width must be greater than 0. You entered " << width;
			return 0;
		}
		if (height <= 0)
		{
			cout << "Error: height must be greater than 0. You entered " << height;
			return 0;
		}
		if (targetWidth <= 0)
		{
			cout << "Error: target width must be greater than 0. You entered " << targetWidth;
			return 0;
		}
		if (targetHeight <= 0)
		{
			cout << "Error: target height must be greater than 0. You entered " << targetHeight;
			return 0;
		}
		if (targetWidth > width)
		{
			cout << "Error: target width must be less than width, " << targetWidth << " is greater than " << width;
			return 0;
		}
		if (targetHeight > height)
		{
			cout << "Error: target height must be less than height, " << targetHeight << " is greater than " << height;
			return 0;
		}

		//Error: <valueName> must be greater than 0. You entered <value>
		//When width, height, targetWidth or targetHeight are less than or equal to 0.
		// E.g.Error: target width must be greater than 0. You entered 0
		// Error : <targetValueName> must be less than <valueName>, <targetValue> is greater than <value>
		// When targetWidth is greater than width or targetHeight is greater than height
		// E.g.Error : target width must be less than width, 88 is greater than 50
		// Error : <targetValue> is a non - integer value
		// When trying to read an integer, but got something that is not valid for an integer.
		// E.g.Error : target width is a non - integer value


		  // save originalWidth since width will change with carving
		originalWidth = width;
		// save originalHeight since height will change with carving
		//originalHeight = height;

		Pixel** image1 = createImage(width, height);
		if (image1 != nullptr) { // new returns nullptr if it fails to allocate array

			if (loadImage(filename, image1, width, height)) {

				// uncomment for part 2
				
				while ((width - targetWidth > 0) || (height - targetHeight > 0)) {
				  if (width - targetWidth > 0) {
					int* verticalSeam = findMinVerticalSeam(image1, width, height);
					//PrintArr(verticalSeam, height);
					removeVerticalSeam(image1, width, height, verticalSeam);
					deleteSeam(verticalSeam);
					width--;
				  }

				  // this is for the extra credit
				  if (height - targetHeight > 0) {
					int* horizontalSeam = findMinHorizontalSeam(image1, width, height);
					removeHorizontalSeam(image1, width, height, horizontalSeam);
					deleteSeam(horizontalSeam);
					height--;
				  }
				}
				

				stringstream ss;
				ss << "carved" << width << "X" << height << "." << filename;
				outputImage(ss.str().c_str(), image1, width, height);
			}
		}

		// call last to remove the memory from the heap
		deleteImage(image1, originalWidth/*, originalHeight*/);
		return 0;
	}
		break;
	case 1:
		//loadImage("sunset200X125.ppm", image, 200, 125);
		//outputImage("outputbro.ppm", image, 200, 125);
		return 0;
		break;
	case 2:
		{
			/*loadImage("sunset200X125.ppm", image, width, height);
			outputImage("outputbro.ppm", image, width, height);
			cout << energy(image, 199, 124, width, height) << endl;*/
			return 0;
		}
		break;
	}
	return 0;
	//deleteImage(image, 200);
}


//int main()
//{
//	string filename;
//	int width = 0;
//	int height = 0;
//	int originalWidth = 0;
//	int originalHeight = 0;
//	int targetWidth = 0;
//	int targetHeight = 0;
//
//	cout << "Input filename: ";
//	cin >> filename;
//
//	// add error checking for width, height, targetWidth, and targetHeight
//	cout << "Input width and height: ";
//	cin >> width;
//	if (cin.fail())
//	{
//		cout << "Error: width is a non-integer value";
//	}
//	cin >> height;
//	if (cin.fail())
//	{
//		cout << "Error: height is a non-integer value";
//	}
//	cout << "Input target width and height: ";
//	cin >> targetWidth;
//	if (cin.fail())
//	{
//		cout << "Error: target width is a non-integer value";
//	}
//	cin >> targetHeight;
//	if (cin.fail())
//	{
//		cout << "Error: target height is a non-integer value";
//	}
//
//	if (width <= 0)
//	{
//		cout << "Error: width must be greater than 0. You entered " << width;
//		return 1;
//	}
//	if (height <= 0)
//	{
//		cout << "Error: height must be greater than 0. You entered " << height;
//	}
//	if (targetWidth <= 0)
//	{
//		cout << "Error: target width must be greater than 0. You entered " << targetWidth;
//	}
//	if (targetHeight <= 0)
//	{
//		cout << "Error: target height must be greater than 0. You entered " << targetHeight;
//	}
//	if (targetWidth > width)
//	{
//		cout << "Error: targetWidth must be less than width, " << targetWidth << " is greater than " << width;
//	}
//	if (targetHeight > height)
//	{
//		cout << "Error: targetHeight must be less than height, " << targetHeight << " is greater than " << height;
//	}
//
//	//Error: <valueName> must be greater than 0. You entered <value>
//	//When width, height, targetWidth or targetHeight are less than or equal to 0.
//	// E.g.Error: target width must be greater than 0. You entered 0
//	// Error : <targetValueName> must be less than <valueName>, <targetValue> is greater than <value>
//	// When targetWidth is greater than width or targetHeight is greater than height
//	// E.g.Error : target width must be less than width, 88 is greater than 50
//	// Error : <targetValue> is a non - integer value
//	// When trying to read an integer, but got something that is not valid for an integer.
//	// E.g.Error : target width is a non - integer value
//
//
//	  // save originalWidth since width will change with carving
//	originalWidth = width;
//	// save originalHeight since height will change with carving
//	originalHeight = height;
//
//	Pixel** image1 = createImage(width, height);
//	if (image1 != nullptr) { // 
//returns nullptr if it fails to allocate array
//
//		if (loadImage(filename, image1, width, height)) {
//
//			// uncomment for part 2
//			/*
//			while ((width - targetWidth > 0) || (height - targetHeight > 0)) {
//			  if (width - targetWidth > 0) {
//				int* verticalSeam = findMinVerticalSeam(image, width, height);
//				removeVerticalSeam(image, width, height, verticalSeam);
//				deleteSeam(verticalSeam);
//				width--;
//			  }
//
//			  // this is for the extra credit
//			  if (height - targetHeight > 0) {
//				int* horizontalSeam = findMinHorizontalSeam(image, width, height);
//				removeHorizontalSeam(image, width, height, horizontalSeam);
//				deleteSeam(horizontalSeam);
//				height--;
//			  }
//			}
//			*/
//
//			stringstream ss;
//			ss << "carved" << width << "X" << height << "." << filename;
//			outputImage(ss.str().c_str(), image1, width, height);
//		}
//	}
//
//	// call last to remove the memory from the heap
//	deleteImage(image1, originalWidth, originalHeight);
//}