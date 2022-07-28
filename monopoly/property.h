#include <string>
#pragma once
class Property {
  public:
  std::string name;
  int cost;
  Property(std::string _name, int _cost) {
    name = _name;
    cost = _cost;
  }
  ~Property() {}
};

