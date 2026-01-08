#pragma once
#include <variant>
#include <string>

namespace iamaprogrammer {
  class Value {
    public:
      Value(std::string value);
      Value(int value);
      Value(double value);
      Value();

      std::string asString() const;
      int asInteger() const;
      double asDouble() const;

    private:
      std::variant<std::string, int, double, nullptr_t> value;
  };
}