#include "gtest/gtest.h"
#include <iostream>
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
  for (int d = start1; d <= end1; ++d)
  {
    for (int e = start2; e<= end2; ++e) {
        for(int w = start3; w<=end3; ++w) {
          output.push_back({d/3.f,e/3.f,w/3.f});
        }
      }
  }
  output.push_back({1, M_PI, 0});
  output.push_back({1, 0, M_PI});
  output.push_back({1, 0, -M_PI});
  output.push_back({1, M_PI, -M_PI});
  output.push_back({1, M_PI, M_PI});
  output.push_back({1, 0, 0});
  return output;

}

INSTANTIATE_TEST_SUITE_P (
  conversionmethod,
  EqualityTest,
  ::testing::ValuesIn(generateTriple(0, 5, 0, 3, -3, 3))
);

int main (int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
