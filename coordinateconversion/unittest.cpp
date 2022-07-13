// #include <iostream>
#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "conversion.h"

using namespace std;
struct EqualityTest : public ::testing::TestWithParam<vector<float>> {
};

TEST_P(EqualityTest, cartesian0) {
  vector<float>nums = GetParam();
  EXPECT_FLOAT_EQ(ConvertFromCartesian(nums[0], nums[1], nums[2])[0], ConvertFromCartesian(nums)[0]);
}

TEST_P(EqualityTest, cartesian1) {
  vector<float>nums = GetParam();
  EXPECT_FLOAT_EQ(ConvertFromCartesian(nums[0], nums[1], nums[2])[1], ConvertFromCartesian(nums)[1]);
}

TEST_P(EqualityTest, cartesian2) {
  vector<float>nums = GetParam();
  EXPECT_FLOAT_EQ(ConvertFromCartesian(nums[0], nums[1], nums[2])[2], ConvertFromCartesian(nums)[2]);
}

TEST_P(EqualityTest, spherical0) {
  vector<float>nums = GetParam();
  EXPECT_FLOAT_EQ(ConvertFromSpherical(nums[0], nums[1], nums[2])[0], ConvertFromSpherical(nums)[0]);
}
TEST_P(EqualityTest, spherical1) {
  vector<float>nums = GetParam();
  EXPECT_FLOAT_EQ(ConvertFromSpherical(nums[0], nums[1], nums[2])[1], ConvertFromSpherical(nums)[1]);
}
TEST_P(EqualityTest, spherical2) {
  vector<float>nums = GetParam();
  EXPECT_FLOAT_EQ(ConvertFromSpherical(nums[0], nums[1], nums[2])[2], ConvertFromSpherical(nums)[2]);
}


vector<vector<float>> generateTriple(int start1, int end1, int start2, int end2, int start3, int end3) {
  vector<vector<float>> output = {};
  for (int d = start1; d <= end1; ++d) {
    for (int e = start2; e<= end2; ++e) {
        for(int w = start3; w<=end3; ++w) {
          output.push_back({d/3.f,e/3.f,w/3.f});
        }
      }
  }
  output.push_back({1, 1, M_PI});
  output.push_back({1, 1, -M_PI});
  return output;

}
vector<vector<float>> generateTriple(int start1, int end1, int start2, int end2, int start3, int end3, int dummy) {
  vector<vector<float>> output = generateTriple(start1, end1, start2, end2, start3, end3);
  output.push_back({1, M_PI, 0});
  output.push_back({1, 0, 0});
  output.push_back({1, M_PI, -M_PI});
  output.push_back({1, M_PI, M_PI});
  output.push_back({0, M_PI, 0});
  output.push_back({0, M_PI, M_PI});
  output.push_back({0, M_PI, -M_PI});
  output.push_back({0, 0, M_PI});
  output.push_back({0, 0, -M_PI});
  output.push_back({1, 0, M_PI});
  output.push_back({1, 0, -M_PI});
  return output;
}

INSTANTIATE_TEST_SUITE_P (
  conversionmethod,
  EqualityTest,
  ::testing::ValuesIn(generateTriple(0, 5, 0, 3, -3, 3, 100))
);


struct CheckTest : public ::testing::TestWithParam<vector<float>> {
};
TEST_P(CheckTest, cartesian) {
  vector<float>nums = GetParam();
  EXPECT_EQ(Check(nums, ConvertFromSpherical(ConvertFromCartesian(nums))), 1);
}

TEST_P(CheckTest, sphericalw) {
  vector<float>nums = GetParam();
  EXPECT_EQ(Check(nums, ConvertFromCartesian(ConvertFromSpherical(nums))), 1);
}

// When converting from spherical to cartesian, if r=0, the cartesian converted
// coordinate triple will always be (0, 0, 0) due to the conversion formula.
// Because of this, the check function will fail as when trying to convert from
// cartesian (0,0,0) to spherical, we would get an undefined result for phi,
// leading to an undefined point, phi, denoted by (-1, -1, -1) in our program to keep it from crashing
// The test method, if run  would see that (0,0,0) != (-1, -1, -1)
// Similarly, if r>0, phi>0, but theta = 0, our the check method will also fail as the converted coordinate in this scenario to cartesian would always be
// (0, 0, z) where z = radius r. However, when converting the coordinate (0, 0, z), it will always result in an undefined point denoted by (-1, -1, -1)
// Even more similarly, if theta = pi in this scenario, our check will once again fail as the converted cartesian coordinate would always be
// (0, 0, -z) where z= radius r, which is undefined when converted back
// These cases are handled by our conversion program by simply skipping over the check, 
// however, it will cause the unit test to fail if we pass in 0 for the first coordinate, or for the second coordinate so as to avoid the unecessasry fail, we do not test out the value of 0 for coord1 or coord2 with generateTriple
INSTANTIATE_TEST_SUITE_P (
  checktest,
  CheckTest,
  ::testing::ValuesIn(generateTriple(1, 5, 1, 3, -3, 3))
);

// This special parameterized test is to make sure that ConvertFromSpherical still works in those conditions that we could not test for above, including when PI is involved
struct SpecialTest : public ::testing::TestWithParam<float> { };

TEST_P(SpecialTest, sphericalz) {
  float r = abs(GetParam());
  float theta = abs(GetParam());
  float phi = GetParam();
  vector<float>nums = { 0, 0, r};
  vector<float>zero = { 0, 0, 0};
  vector<float>one = {0, 0, 1};
  vector<float>n_one = {0, 0, -1};
  EXPECT_EQ(ConvertFromSpherical(r, 0, phi), nums);
  EXPECT_EQ(ConvertFromSpherical(0, theta, phi), zero);
  EXPECT_EQ(ConvertFromSpherical(0, 0, phi), zero);
  EXPECT_EQ(ConvertFromSpherical(0, 0, 0), zero);
  EXPECT_EQ(ConvertFromSpherical(1, 0, M_PI), one);
  EXPECT_EQ(ConvertFromSpherical(1, 0, -M_PI), one);
  EXPECT_EQ(ConvertFromSpherical(1, M_PI, 0), n_one);
  EXPECT_EQ(ConvertFromSpherical(1, M_PI, M_PI), n_one);
  EXPECT_EQ(ConvertFromSpherical(1, M_PI, -M_PI), n_one);
  EXPECT_EQ(ConvertFromSpherical(1, 0, -M_PI), one);
  EXPECT_EQ(ConvertFromSpherical(0, M_PI, 1), zero);
  EXPECT_EQ(ConvertFromSpherical(0, M_PI, -M_PI), zero);
  EXPECT_EQ(ConvertFromSpherical(0, M_PI, M_PI), zero);
  EXPECT_EQ(ConvertFromSpherical(0, 0, M_PI), zero);
  EXPECT_EQ(ConvertFromSpherical(0, 0, -M_PI), zero);

}

vector<float> generateNum(int start, int end) {
  vector<float> output = {};
  for (int d = start; d <= end; ++d) {
    output.push_back(d/3.f);
  }
  return output;
}

INSTANTIATE_TEST_SUITE_P (
  undefinedpoints,
  SpecialTest,
  ::testing::ValuesIn(generateNum(-3, 3))
);

/*
 * Confirm check works
 * Confirm that convert from spherical is outputting correct answers using edgecases and hardcoded examples
 * Confirm that cartesian is producing correct answers
 * DONE: Input sanitization
*/

int main (int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
