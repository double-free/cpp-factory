#pragma once

#include "Animal.hpp"

namespace pet {
  class Cat: public base::Animal {
  public:
    Cat(int id, std::string name)
      :base::Animal(id, name)
    {}

    std::string sound() const final {
      return "mew, mew";
    }
  };
} /* pet */
