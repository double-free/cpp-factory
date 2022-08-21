#pragma once

#include "../factory/Factory.hpp"

#include <iostream>

namespace base {
  class Animal {
  public:
    Animal(int id, std::string name)
      : id_(id), name_(name) {}

    void speek() const {
      std::cout << "\"" << sound() << "\" from animal with id "
      << id_ << ", name " << name_ << "\n";
    }

    virtual std::string sound() const {
      return "muted";
    }

  private:
    int id_;
    std::string name_;
  };

  using AnimalFactory = yy::StaticFactory<Animal, int, std::string>;
} /* base */
