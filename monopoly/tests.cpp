#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "game.h"

using::testing::AtLeast;
using::testing::Return;
using::testing::_;



class MockPlayer : public IPlayer {
public:
  MOCK_METHOD(int, swapTurn, (Player p), (override));
  MOCK_METHOD(int, updateBalance, (int amount), (override));
  MOCK_METHOD(int, updatePosition, (int amount), (override));
  MOCK_METHOD(void, addProperty, (Property prop), (override));
  MOCK_METHOD(void, rmProperty, (int index), (override));
  MOCK_METHOD(int, tradeMoney, (bool sendOrReceive, int amount, Player p), (override));
};

TEST(PlayerTest, swapturn) {
  MockPlayer p1;
  MockPlayer p2;
  int p1turn = p1.turn;
  int p2turn = p2.turn;
  EXPECT_CALL(p1, swapTurn(p2).Times(1));
  EXPECT_EQ(p1.turn, p2turn);
  EXPECT_EQ(p2.turn, p1turn);
}



int main (int argc, char *argv[])
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
