#include "example/Cat.hpp"
#include "example/Dog.hpp"

namespace pet {
  REGISTER_OBJECT(base::AnimalFactory, Cat);
  REGISTER_OBJECT(base::AnimalFactory, Dog);
} /* pet */

int main(int argc, char const *argv[]) {
  auto cat =
    base::AnimalFactory::factory().create("Cat", 1, "kitty");

  auto dog =
    base::AnimalFactory::factory().create("Dog", 1, "snoopy");

  cat->speek();
  dog->speek();

  return 0;
}
