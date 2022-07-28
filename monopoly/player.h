#include <iostream>
#include <vector>
#include "property.h"
#include "tests.h"

#pragma once

class Player : IPlayer{
public:
  std::string name;
  int position = 0;
  int turn;
  int balance = 1500;
  std::vector<Property> properties = {};

  Player(std::string _name = "Player", int _turn = 1) {
    name = _name;
    turn = _turn;
  }
  
  int swapTurn(Player p) {
    int newTurn = p.turn;
    int tmp = turn;
    turn = newTurn;
    p.turn = tmp;
    return turn;
  }

  int updateBalance(int amount) {
    balance+=amount;
    return balance;
  }

  int updatePosition(int amount) {
    position+=amount;
    return position;
  }

  void addProperty(Property prop) {
    properties.push_back(prop);
  }

  void rmProperty(int index) {
    properties.erase(properties.begin()+index);
  }
  
  int tradeMoney(bool sendOrReceive, int amount, Player p) {
    // send
    if (sendOrReceive) {
      updateBalance(-amount);
      p.updateBalance(amount);
    // receive
    } else {
      updateBalance(amount);
      p.updateBalance(amount);
    }
    return balance;
  }


  ~Player() {}
};
