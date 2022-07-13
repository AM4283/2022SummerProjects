#ifndef CONVERSION
#define CONVERSION
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#define DELTA 0.0001
using namespace std;

// Order: ISO 80000-2:2019 Convention (physics)
// r, theta, phi (radius, "vertical angle (polar angle w/ respect to polar axis)", "horizontal angle (azimuth angle)") 
// if x and y = 0, phi returns -1
// will return a value in which r >=0, 0<=theta<=pi, -pi<=phi<=+pi
vector<float> ConvertFromCartesian(float x, float y, float z);
// hack to allow vector input
vector<float> ConvertFromCartesian(vector<float> cartesian) ;
// takes input (r, theta, phi) assumes theta is the "vertical angle", phi is the
// "horizontal angle", returns corresponding x,y,z
// r must be >= 0, 0<=theta<=+pi, -pi<=phi<=+pi
vector<float> ConvertFromSpherical(float r, float theta, float phi);
// hack to allow vector input
vector<float> ConvertFromSpherical(vector<float> spherical);
// Prints Converted coordinates
void PrintCoordinates(vector<float> values);
void PrintCoordinates(float num1, float num2, float num3);
// sanity Check to see if the answer is accurate enough due to floating point
// math
int Check(vector<float> original, vector<float> reverse);
// takes the input either x, y, z or r, theta, phi and returns the corresponding 
// coordinate
void GetCoords(int input, float coord1, float coord2, float coord3);
#endif
