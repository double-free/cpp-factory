#pragma once

#include "Animal.hpp"

namespace pet {
  class Dog: public base::Animal {
  public:
    Dog(int id, std::string name)
      :base::Animal(id, name)
    {}

    std::string sound() const final {
      return "won, won";
    }
  };
} /* pet */
