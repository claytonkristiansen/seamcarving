#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include "functions.h"

struct Pixel {
  int r = 0; // red
  int g = 0; // green
  int b = 0; // blue
};

// Implemented for you

Pixel** createImage(int width, int height);
void deleteImage(Pixel** image, int width/*, int height*/);


// Implement for part 1

int* createSeam(int length);
void deleteSeam(int* seam);
bool loadImage(std::string filename, Pixel** image, int width, int height);
bool outputImage(std::string filename, Pixel** image, int width, int height);
int energy(Pixel** image, int x, int y, int width, int height);


// Implement for part 2

//This function will traverse through an image starting at the first row at the given start_col. See “Loading a vertical seam” below for how the traversal works. See “Seam Representation” below for how seams are represented.
//The function returns the total energy of the seam
//The first parameter is a 2d array of Pixels(structs) that hold a color value
//The second parameter is the column to start the seam.
//The third parameter is the width of the array(i.e.the number of columns) needed for traversing the array
//The fourth parameter is the height of the array(i.e.the number of rows) needed for traversing the array.
//The fifth parameter is an array to be loaded with column values for each row.
//Pseudocode
//Set seam for the first row to the starting column
//Initialize total energy to the energy for pixel(start_col, 0)
//For each subsequent row
//Calculate the energy of each possible next column
//Set the seam for current row to the column with the minimal energy
//Add the minimal energy to the total energy
//Return total energy
int loadVerticalSeam(Pixel** image, int start_col, int width, int height, int* seam);

int loadHorizontalSeam(Pixel** image, int start_row, int width, int height, int* seam);

//This function will traverse through each column, loading its seam in order to find the seam with lowest energy.See “Finding a Minimal Vertical Seam” below for how this works.
//The function returns a pointer to a seam that is the seam with minimal energy.
//The first parameter is a 2d array of Pixels(structs) that hold a color value
//The second parameter is the width of the array(i.e.the number of columns) needed for traversing the array
//The third parameter is the height of the array(i.e.the number of rows) needed for traversing the array.
//Pseudocode
//Set minimal energy to the result of loading the seam for the first column
//Note minimal seam was loaded by function that returned minimal energy
//For each column
//Get energy for the columnand load candidate seam
//If the energy is less than minimal energy
//Set minimal energy to energy
//Update minimal seam to be the candidate seam
//Note : you will have to create seams to pass to loadVerticalSeam
//You cannot have a memory leak.
int* findMinVerticalSeam(Pixel** image, int width, int height);

int* findMinHorizontalSeam(Pixel** image, int width, int height);

//This function removes the pixels from the image corresponding to the vertical seam.See “Removing a Vertical seam” below for how the removal works.See “Seam Representation” below for how seams are represented.
//The first parameter is a 2d array of Pixels(structs) that hold a color value
//The second parameter is the width of the array(i.e.the number of columns) needed for traversing the array
//The third parameter is the height of the array(i.e.the number of rows) needed for traversing the array.
//The fourth parameter is an array indicating which pixels should be removed.
//Pseudocode
//For each row
//Remove pixel(seam[row], row) - note that seam[row] will be the column.
void removeVerticalSeam(Pixel** image, int width, int height, int* verticalSeam);

void removeHorizontalSeam(Pixel** image, int width, int height, int* horizontalSeam);

#endif