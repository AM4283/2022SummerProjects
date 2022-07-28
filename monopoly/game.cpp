#include "game.h"

Game::Game(int _numPlayers, std::vector<Player> _players) {
  numPlayers = _numPlayers;
  for (Player p : _players) {
    players.push_back(p);
  }
  if (numPlayers >= 2 && numPlayers <= 8) {
    isValid = true;
  }
  if (isValid) {
    gameMoney -= numPlayers * 1500;
    playerMoney += numPlayers * 1500;
  }
}

// int main (int argc, char *argv[])
// {
//   // Production Environment
//   std::vector<Player> players = {};
//   Player p1("Patrick");
//   Player p2("Spongebob", 2);
//   Player p3("Squidward", 3);
//   players.push_back(p1);
//   players.push_back(p2);
//   players.push_back(p3);

//   Game gm(3, players);
//   
//   // for (Property p : properties) {
//   //   gm.availableProperties.push_back(p);
//   // }

//   std::cout << gm.gameMoney << "\n";

//   for (Player p : gm.players) {
//     std::cout << p.name << " " << p.balance << "\n";
//   }
//   // for (Property p : gm.availableProperties) {
//   //   std::cout << p.name << " " << p.cost << "\n";
//   // }
//   return 0;


//   // Testing Environment
// }
