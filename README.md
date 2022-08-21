# cpp-factory

A header-only cpp factory with a convenient MACRO to register classes.

It comes extremely handy and convenient with supports for dynamic libs.

Simply copy `factory/Factory.hpp` to your project.

## 1 Dependency

C++14 or above, for `std::make_unique`. You can replace it with uglier old style code for compatibility.

## 2 Basic usage

Will use the code in `example` to explain its usage.

1. define your factory

```cpp
namespace base {
  using AnimalFactory = yy::StaticFactory<Animal, int, std::string>;
} /* base */
```

2. register class with its name

```cpp
namespace pet {
  REGISTER_OBJECT(base::AnimalFactory, Cat);
  REGISTER_OBJECT(base::AnimalFactory, Dog);
} /* pet */
```

3. create instance with class name

```cpp
auto cat = base::AnimalFactory::factory().create("Cat", 1, "kitty");
```

## 3 Advanced usage with dynamic lib

- In your dynamic lib, you need to expose the factory with a C-function to avoid mangling

- In your executable, load the symbol of the C-function you defined, and `merge` the result

Example:

```cpp
extern "C"
{
// This is to expose all registered classes of a dynamic library
const auto& AnimalRegistry()
{
    return AnimalRegistry::factory().registry();
}
}
```
