#include "value.h"

namespace iamaprogrammer {
  Value::Value(std::string value): value(value) {
    
  }
  
  Value::Value(int value): value(value) {

  }

  Value::Value(double value): value(value) {

  }

  Value::Value(): value(nullptr) {

  }

  std::string Value::asString() {
    return std::get<std::string>(this->value);
  }

  int Value::asInteger() {
    return std::get<int>(this->value);
  }

  double Value::asDouble() {
    return std::get<double>(this->value);
  }
}