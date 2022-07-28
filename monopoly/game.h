#include "property.h"
#include "player.h"

class Game {
public:
  int gameMoney = 20580;
  bool isValid = false;
  std::vector<Player> players = {};
  std::vector<Property> availableProperties = {};

  Game(int _numPlayers, std::vector<Player> _players);

private:
  int numPlayers = 0;
  int playerMoney = 0;
};
