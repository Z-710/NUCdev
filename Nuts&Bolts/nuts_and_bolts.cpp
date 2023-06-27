#include <iostream>
#include "nuts_and_bolts.hpp"

// member functions of Nut
Nut::Nut(int s) : size_ {s} {}

bool Nut::operator==(const Bolt& b) const {
  return nutFitsBolt(*this, b);
}

bool Nut::operator<(const Bolt& b) const {
  return nutSmallerThanBolt(*this, b);
}

bool Nut::operator<=(const Bolt& b) const {
  return nutSmallerThanBolt(*this, b) || nutFitsBolt(*this, b);
}

bool Nut::operator>(const Bolt& b) const {
  return !(nutSmallerThanBolt(*this, b) ||
              nutFitsBolt(*this, b));
}

bool Nut::operator>=(const Bolt& b) const {
  return !(nutSmallerThanBolt(*this, b));
}

// member functions of Bolt
Bolt::Bolt(int s) : size_ {s} {}

bool Bolt::operator==(const Nut& n) const {
  return nutFitsBolt(n, *this);
}

bool Bolt::operator<(const Nut& n) const {
  return !(nutSmallerThanBolt(n, *this) || nutFitsBolt(n, *this));
}

bool Bolt::operator<=(const Nut& n) const {
  return !(nutSmallerThanBolt(n, *this));
}

bool Bolt::operator>(const Nut& n) const {
  return nutSmallerThanBolt(n, *this);
}

bool Bolt::operator>=(const Nut& n) const {
  return nutSmallerThanBolt(n, *this) || nutFitsBolt(n, *this);
}

// Helper functions
bool nutSmallerThanBolt(const Nut& n, const Bolt& b) {
  return n.size_ < b.size_;
}

bool nutFitsBolt(const Nut& n, const Bolt& b) {
  return n.size_ == b.size_;
}

std::ostream& operator<<(std::ostream& out, const Nut& n) {
  out << n.size_;
  return out;
}

std::ostream& operator<<(std::ostream& out, const Bolt& b) {
  out << b.size_;
  return out;
}


