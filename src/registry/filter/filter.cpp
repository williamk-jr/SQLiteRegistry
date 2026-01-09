#include "filter.h"

namespace iamaprogrammer {
  Filter::Filter() {}

  Filter::Filter(FilterExpression expression) {
    this->expression = expression.expression;
  }

  Filter::Filter(FilterCompoundExpression expression) {
    this->expression = expression.expression;
  }

  std::string Filter::toSql() {
    return this->expression;
  }

  bool Filter::isEmpty() {
    return this->expression.empty();
  }
}