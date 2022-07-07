#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#define DELTA 0.0001
using namespace std;

// Order: r, theta, phi (radius, "vertical angle", "horizontal angle") if x and y = 0, phi returns -1
vector<float> convertfromcartesian(float x, float y, float z) {
  float r = sqrt(x*x+y*y+z*z);
  float theta = acos(z/r);
  float phi;
  if (x > 0) {
    phi = atan(y/x);
  } else if (x < 0 && y >= 0) {
    phi = atan(y/x) + M_PI;
  } else if (x < 0 && y < 0) {
    phi = atan(y/x) - M_PI;
  } else if (x == 0 && y > 0) {
    phi = M_PI/2;
  } else if (x == 0 && y < 0) {
    phi = -M_PI/2;
  } else {
    phi = -1;
  }
  vector<float> points = {r, theta, phi};
  return points;
}

// hack to allow vector input
vector<float> convertfromcartesian(vector<float> cartesian) {
  return convertfromcartesian(cartesian[0], cartesian[1], cartesian[2]);
}

// takes input (r, theta, phi) assumes theta is the "vertical angle", phi is the "horizontal angle", returns corresponding x,y,z
vector<float> convertfromspherical(float r, float theta, float phi) {
  float x = r*cos(phi)*sin(theta);
  float y = r*sin(phi)*sin(theta);
  float z = r*cos(theta);
  vector<float> points = {x, y, z};
  return points;
}

// hack to allow vector input
vector<float> convertfromspherical(vector<float> spherical) {
  return convertfromspherical(spherical[0], spherical[1], spherical[2]);
}

void printstuff(vector<float> values) {
  cout << "Converted coordinate: " << values[0] << ", " << values[1] << ", " << values[2] << endl;
}

// sanity check to see if the answer is accurate enough due to floating point math
void check(vector<float> original, vector<float> reverse) {
  for (int i = 0; i<3; i++) {
    if (!(abs(original[i] - reverse[i]) < DELTA)) {
      cerr << "\nError checking answer, expected " << original[i] << " got " << reverse[i] << endl;
      exit(EXIT_FAILURE);
    }
  }
  return;
}

// takes the input either x, y, z or r, theta, phi
void getcoords(int input, float coord1, float coord2, float coord3) {
  if (isnan(coord1)) {
    if (input == 1) {
      cout << "Enter coordinate x, y, z\n";
    } else {
      cout<< "Enter coordinate r, theta, phi where theta is the inclination from the z direction and that phi is measured from the cartesian x-axis \n";
    }
    cin >> coord1 >> coord2 >> coord3;
    if (isnan(coord1) || isnan(coord1) || isnan(coord2)) {
      cerr << "Invalid input" << endl;
      exit(EXIT_FAILURE);
    } 
  }
  printf("Coordinate: %0.3f %0.3f %0.3f\n", coord1, coord2, coord3);
  vector<float> nums = {coord1, coord2, coord3};

  if (input == 1) {
    // Check to see if the conversion back is within error of less than 1 ten thousandth
    check(nums, convertfromspherical(convertfromcartesian(coord1, coord2, coord3)));
    printstuff(convertfromcartesian(coord1, coord2, coord3));
  } else {
    check(nums, convertfromcartesian(convertfromspherical(coord1, coord2, coord3)));
    printstuff(convertfromspherical(coord1, coord2, coord3));
  }
}

int main(int argc, char* argv[]) {
  for (int i = 1; i<argc; i++) {
    if (!(isdigit(*argv[i]))) {
      cout << "Error: Correct argument syntax: command [OPTION] [COORDINATE 1 2 3]" << endl;
      return 1;
    }
  }

  int input;
  // if there is only one argument (just the program):
  if (argc == 1) {
    cout<< "Convert from cartesian to spherical (1) or spherical to cartesian (2) ?\n";
    cin >> input;
    if (input == 1 || input == 2) {
      // NAN passed in as dummy values into getcoords()
      getcoords(input, NAN, NAN, NAN);
    } else {
      cerr << "Invalid input" << endl;
      return 1;
    }
  // if there are 2 or 5 arguments
  } else if (argc == 2 || argc == 5) {
    // check the second argument to see if it is a 1 or a 2
    switch(*argv[1]) {
      case '1' : input = 1;
        // if there are 5 arguments, the last 3 are coordinates and passed into getcoords
        if (argc == 5) {
          getcoords(input, atof(argv[2]), atof(argv[3]), atof(argv[4]));
        } else {
          getcoords(input, NAN, NAN, NAN);
        }
        break;
      case '2' : input = 2;
        if (argc == 5) {
          getcoords(input, atof(argv[2]), atof(argv[3]), atof(argv[4]));
        } else {
          getcoords(input, NAN, NAN, NAN);
        }
        break;
      // if the second argument is not 1 or 2
      default: cout << "Error: Correct argument syntax: command [OPTION] [COORDINATE 1 2 3]" << endl;
    }
  }
  // if there are arguments 2<5 or >5
  else {
    cout << "Error: Correct argument syntax: command [OPTION] [COORDINATE 1 2 3]" << endl;
    return 1;
  } 
  return 0;
}
