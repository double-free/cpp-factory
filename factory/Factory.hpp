
#pragma once

#include <string>
#include <functional>
#include <memory>
#include <unordered_map>

namespace yy
{
// create class T with arguments
template <typename T, typename... Args>
class Factory
{
public:
  using Ctor = std::function<std::unique_ptr<T>(Args...)>;
  using Container = std::unordered_map<std::string, Ctor>;

  // register ctor for DerivedT with name
  template <typename DerivedT>
  void registerType(std::string name)
  {
      static_assert(std::is_base_of<T, DerivedT>::value,
                    "must provide a derived class");

      if (ctors_.find(name) != ctors_.end())
      {
          throw std::invalid_argument("registered same type [" + name + "] twice!");
      }

      Ctor ctor = [](Args &&...args) -> std::unique_ptr<T> {
          return std::make_unique<DerivedT>(std::forward<Args>(args)...);
      };
      ctors_.emplace(name, ctor);
  }

  std::unique_ptr<T> create(std::string name, Args &&...args) const
  {
      auto iter = ctors_.find(name);
      if (iter == ctors_.end())
      {
          throw std::invalid_argument("type [" + name + "] is never registered!");
      }
      return iter->second(std::forward<Args>(args)...);
  }

  const Container &registry() const
  {
      return ctors_;
  }

  void merge(const Container &another)
  {
      // merge with another factory
      for (const auto &[k, v] : another)
      {
          if (ctors_.find(k) != ctors_.end())
          {
              throw std::invalid_argument("find duplicated key when merging: " + k);
          }
          ctors_.emplace(k, v);
      }
  }

private:
  Container ctors_;
};

template <typename T, typename... Args>
class StaticFactory
{
public:
  using Container = typename Factory<T, Args...>::Container;

  template <typename DerivedT>
  struct Registrar
  {
      explicit Registrar(std::string const &name)
      {
          factory().template registerType<DerivedT>(name);
      }
  };

  static auto &factory()
  {
      static Factory<T, Args...> factory;
      return factory;
  }
};

} // namespace yy

// "FACTORY" can have namespace, but "CLASS" can not
// this effectively call the constructor of StaticFactory::Registrar
#define REGISTER_OBJECT(FACTORY, CLASS)                                 \
inline static FACTORY::Registrar<CLASS> &___get##CLASS##Registrar() \
{                                                                   \
  static FACTORY::Registrar<CLASS> registrar(#CLASS);             \
  return registrar;                                               \
}                                                                   \
static FACTORY::Registrar<CLASS> &___##CLASS##Registrar = ___get##CLASS##Registrar()
