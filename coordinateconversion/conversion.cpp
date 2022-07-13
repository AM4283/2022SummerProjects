#include "conversion.h"
using namespace std;

// Order: ISO 80000-2:2019 Convention (physics)
// r, theta, phi (radius, "vertical angle (polar angle w/ respect to polar axis)", "horizontal angle (azimuth angle)") 
// if x and y = 0, theta = 0, y = 0
// will return a value in which r >=0, 0<=theta<=pi, -pi<=phi<=+pi
vector<float> ConvertFromCartesian(float x, float y, float z) {
  float r = sqrt(x * x + y * y + z * z);
  float theta = acos(z / r);
  float phi;
  if (x > 0) {
    phi = atan(y / x);
  } else if (x < 0 && y >= 0) {
    phi = atan(y / x) + M_PI;
  } else if (x < 0 && y < 0) {
    phi = atan(y / x) - M_PI;
  } else if (x == 0 && y > 0) {
    phi = M_PI / 2;
  } else if (x == 0 && y < 0) {
    phi = -M_PI / 2;
  } else {
    r = -1;
    theta = -1;
    phi = -1;
  }
  vector<float> points = {r, theta, phi};
  return points;
}

// hack to allow vector input
vector<float> ConvertFromCartesian(vector<float> cartesian) {
  return ConvertFromCartesian(cartesian[0], cartesian[1], cartesian[2]);
}


// takes input (r, theta, phi) assumes theta is the "vertical angle", phi is the
// "horizontal angle", returns corresponding x,y,z
// r must be >= 0, 0<=theta<=+pi, -pi<=phi<=+pi
vector<float> ConvertFromSpherical(float r, float theta, float phi) {
  float x = r * cos(phi) * sin(theta);
  float y = r * sin(phi) * sin(theta);
  float z = r * cos(theta);

  // In this scenario, if theta is pi, we get an arbitrarily close number to 0 returned as the x coordinate via the math functions used, so we must instead manually specify the output
  if (theta == M_PI) {
    x = 0;
    y = 0;
    z = -r;
  } else if (theta == 0) {
    x = 0;
    y = 0;
    z = r;
  }
  vector<float> points = {x, y, z};
  return points;
}

// hack to allow vector input
vector<float> ConvertFromSpherical(vector<float> spherical) {
  return ConvertFromSpherical(spherical[0], spherical[1], spherical[2]);
}

// Prints Converted coordinates
void PrintCoordinates(vector<float> values) {
  cout << "Converted coordinate: (" << values[0] << ", " << values[1] << ", "
       << values[2] << ")" << endl;
}

// hack to allow single number input
void PrintCoordinates(float num1, float num2, float num3) {
  vector<float> values = {num1, num2, num3};
  PrintCoordinates(values);
}

int Check(vector<float> original, vector<float> reverse) {
  // hack for getting around scenrios when we convert from spherical coordinates, and
  // r>0, theta>0, and phi = PI or -PI, in this scenario, the returned coordinate in cartesian
  // will exist, however, when converting back to spherical, the phi value will be the opposite
  // of the one used to get that coordinate everytime due to the "looping" nature of the unit circle
  for (int i = 0; i < 3; i++) {
    if (!(abs(original[i] - reverse[i]) < DELTA)) {
      cerr << "\nError Checking answer on coordinate " << i << ", expected " << original[i] << " got "
           << reverse[i] << endl;
      return -1;
    }
  }
  return 1;
}
// takes the input either x, y, z or r, theta, phi and returns the corresponding 
// coordinate
void GetCoords(int input, float coord1, float coord2, float coord3) {
  if (isnan(coord1)) {
    if (input == 1) {
      cout << "Enter coordinate (x, y, z)\n";
    } else {
      cout << "Enter coordinate (r, θ, φ) where θ is the inclination "
              "from the z direction and φ is measured from the "
              "cartesian x-axis\n";
      cout << "Input must meet: r ∈ [0, ∞), θ ∈ [0, π], φ ∈ [-π, π) \n";
    }
    cin >> coord1 >> coord2 >> coord3;
    if(cin.fail()) //cin.fail() checks to see if the value in the cin
					//stream is the correct type, if not it returns true,
					//false otherwise.
	{
	  cin.clear(); //This corrects the stream.
	  cin.ignore(); //This skips the left over stream data.
	  cerr << "Invalid input, please enter floats only." << endl;
      exit(EXIT_FAILURE);

	}
  }
  // printf("Coordinate: (%0.3f, %0.3f, %0.3f)\n", coord1, coord2, coord3);
  cout << "Coordinate: (" << coord1 << ", " << coord2 << ", " << coord3 << ")\n";
  vector<float> nums = {coord1, coord2, coord3};

  if (input == 1) {
    // Check to see if the conversion back is within error of less than 1 ten
    // thousandth
    // The check will fail if x and y are = 0, since this will result in an undefined point, represented by the formula used above as the point (-1, -1, -1). The check method will try to convert (-1, -1, -1) back to cartesian and realize that it does not work, so we must iron this edge case out by skipping the check and simply returning the undefined point
    if (nums[0] == 0 && nums[1] == 0) {
      cout << "Undefined point in the spherical system.\n";
      PrintCoordinates(ConvertFromCartesian(coord1, coord2, coord3));
    } else if (Check(nums,
          ConvertFromSpherical(ConvertFromCartesian(coord1, coord2, coord3))) == 1) {
      cout << "Convention: (r, θ, φ) where θ is the inclination from z direction and "
            "φ is measured from the cartesian x-axis\n";
      PrintCoordinates(ConvertFromCartesian(coord1, coord2, coord3));
    } else { exit(EXIT_FAILURE); }
  } else {
    // PrintCoordinates(ConvertFromSpherical(coord1, coord2, coord3));
    if (coord1 < 0 || coord2 < 0 || coord2 > M_PI || coord3 < -M_PI || coord3 > M_PI ) {
      cout << "Invalid input: Input must meet: r ∈ [0, ∞), θ ∈ [0, π], φ ∈ [-π, π)\n";
      cout << M_PI;
      exit(EXIT_FAILURE);
    }
    if (nums[0] == 0|| nums[1] == 0 || nums[1] == M_PI) {
      // Check will fail in these instances, since whenever r=0, the cartesian coordinate will be (0, 0, 0), and when converting (0, 0, 0)
      // back to spherical, we get an undefined point noted by (-1, -1, -1) as to not break our program, so we must handle this case separately
      // and skip the check altogether, since we know it will result in (0, 0, 0)
      // Furthermore, we also know that if theta is 0, our resulting point will not have any x or y distance, being (0, 0, r) where r is our radius. This trips up our program yet again because the cartesian point (0, 0, z) where z!=0 is undefined in the spherical system, denoted by (-1, -1, -1), so we must handle this scenario as well
      // Interestingly, a similar problem arises when theta = pi, but instead we are returned with a cartesian point (0, 0, -r), which is undefined if converted back from the cartesian to spherical system
      PrintCoordinates(ConvertFromSpherical(coord1, coord2, coord3));
    // furthermore, the check would fail anyway since the cartesian coordinate returned is undefined in the spherical system, so we must skip it
    } else if (Check(nums,
          ConvertFromCartesian(ConvertFromSpherical(coord1, coord2, coord3))) == 1) {
      PrintCoordinates(ConvertFromSpherical(coord1, coord2, coord3));
    } else { exit(EXIT_FAILURE); }
  }
}

int main(int argc, char *argv[]) {
  // cout << argc << "Arguments\n" << argv[1] << "\n";
  for (int i = 1; i < argc; i++) {
    if (*argv[i] == '-' && atof(argv[i]) < 0) { continue; }
    else if (!(isdigit(*argv[i]))) {
      cout << "Error: Correct argument syntax: command [OPTION] [COORDINATE 1 2 3]\n";
      cout << "OPTION: 1 - Cartesian to Spherical, 2 - Spherical to Cartesian" << endl;
      return 1;
    }
  }

  int input;
  // if there is only one argument (just the program):
  if (argc == 1) {
    cout << "Convert from cartesian to spherical (1) or spherical to cartesian "
            "(2) ?\n";
    cin >> input;
    if (input == 1 || input == 2) {
      // NAN passed in as dummy values into GetCoords()
      // Nice!
      GetCoords(input, NAN, NAN, NAN);
    } else {
      cerr << "Invalid input, please enter a valid choice" << endl;
      return 1;
    }
    // if there are 2 or 5 arguments
  } else if (argc == 2 || argc == 5) {
    // Check the second argument to see if it is a 1 or a 2
    switch (*argv[1]) {
    case '1':
      input = 1;
      // if there are 5 arguments, the last 3 are coordinates and passed into
      // GetCoords
      if (argc == 5) {
        GetCoords(input, atof(argv[2]), atof(argv[3]), atof(argv[4]));
      } else {
        GetCoords(input, NAN, NAN, NAN);
      }
      break;
    case '2':
      input = 2;
      if (argc == 5) {
        GetCoords(input, atof(argv[2]), atof(argv[3]), atof(argv[4]));
      } else {
        GetCoords(input, NAN, NAN, NAN);
      }
      break;
    // if the second argument is not 1 or 2
    default:
      cout << "Error: Correct argument syntax: command [OPTION] [COORDINATE 1 "
              "2 3]\n";
      cout << "OPTION: 1 - Cartesian to Spherical, 2 - Spherical to Cartesian" << endl;
    }
  }
  // if there are arguments 2<5 or >5
  else {
    cout << "Error: Correct argument syntax: command [OPTION] [COORDINATE 1 2 3]\n";
    cout << "OPTION: 1 - Cartesian to Spherical, 2 - Spherical to Cartesian" << endl;
    return 1;
  }
  return 0;
}
