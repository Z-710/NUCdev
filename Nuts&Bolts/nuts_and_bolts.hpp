#ifndef NUTS_AND_BOLTS_HPP
#define NUTS_AND_BOLTS_HPP

#include <iostream>

// forward declaration of Bolt class
// (we need to refer to it in declaring the Nut class)
class Bolt;

class Nut {
 private:
  int size_;
 public:
  explicit Nut(int s);
  bool operator==(const Bolt&) const;
  bool operator<(const Bolt&) const;
  bool operator<=(const Bolt&) const;
  bool operator>(const Bolt&) const; 
  bool operator>=(const Bolt&) const; 
  friend bool nutSmallerThanBolt(const Nut&, const Bolt&);
  friend bool nutFitsBolt(const Nut&, const Bolt&);
  friend std::ostream& operator<<(std::ostream&, const Nut&);
};

class Bolt {
 private:
  int size_;
 public:
  explicit Bolt(int s);
  bool operator==(const Nut&) const;
  bool operator<(const Nut&) const;
  bool operator<=(const Nut&) const;
  bool operator>(const Nut&) const;
  bool operator>=(const Nut&) const;
  friend bool nutSmallerThanBolt(const Nut&, const Bolt&);
  friend bool nutFitsBolt(const Nut&, const Bolt&);
  friend std::ostream& operator<<(std::ostream&, const Bolt&);
};
#endif      // NUTS_AND_BOLTS_HPP
