// #include "game.h"
#include "property.h"

class IPlayer  {
  public:
  virtual int swapTurn(Player p) = 0;
  virtual int updateBalance(int amount) = 0;
  virtual int updatePosition(int amount) = 0;
  virtual void addProperty(Property prop) = 0;
  virtual void rmProperty(int index) = 0;
  virtual int tradeMoney(bool sendOrReceive, int amount, Player p) = 0;
};
