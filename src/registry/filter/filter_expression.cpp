#include "filter_expression.h"

namespace iamaprogrammer {
  FilterExpression::FilterExpression(std::string expression) : expression(expression) {}

  FilterExpression FilterExpression::comparison(std::string name, FilterComparison operation, std::string type) {
    return FilterExpression(name + mapComparison(operation) + type);
  }

  FilterExpression FilterExpression::comparison(std::string name, FilterComparison operation, float type) {
    return FilterExpression(name + mapComparison(operation) + std::to_string(type));
  }

  FilterExpression FilterExpression::comparison(std::string name, FilterComparison operation, int type) {
    return FilterExpression(name + mapComparison(operation) + std::to_string(type));
  }

  FilterExpression FilterExpression::isNull(std::string name) {
    return FilterExpression(name + " IS NULL");
  }

  std::string FilterExpression::mapComparison(FilterComparison operation) {
    switch (operation) {
      case EQUALS:
        return " == ";
      case NOT_EQUALS:
        return " != ";
      case LESS_THAN:
        return " < ";
      case GREATER_THAN:
        return " > ";
      case LESS_THAN_EQUAL_TO:
        return " <= ";
      case GREATER_THAN_EQUAL_TO:
        return " >= ";
    }
  }
}