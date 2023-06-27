#ifndef FARM_HPP_
#define FARM_HPP_

#include <iostream>
#include <vector>
#include <map>

struct Inventory {
  int hay {};
  int eggs {};
  int chickens {};
  // spaceship operator lets us use all 6 comparison operations
  // between two Inventory objects
  auto operator<=>(const Inventory& other) const = default;
  // To help in debugging you can print out an Inventory as 
  // usual: Inventory state {}; std::cout << state;
  friend std::ostream& operator<<(std::ostream& out,
                                  const Inventory& state) {
    out << "hay: " << state.hay << '\n';
    out << "eggs: " << state.eggs << '\n';
    out << "chickens: " << state.chickens << '\n';
    return out;
  }
};

// first parameter is starting state, 
// second parameter is target number of eggs
int daysForEggs(const Inventory&, int);

#endif      // FARM_HPP_
