#include "filter_compound_expression.h"
namespace iamaprogrammer {
  FilterCompoundExpression::FilterCompoundExpression(std::string expression) : expression(expression) {

  }

  FilterCompoundExpression FilterCompoundExpression::logical(FilterExpression expression1, FilterLogical operation, FilterExpression expression2) {
    return FilterCompoundExpression("(" + expression1.expression + mapLogical(operation) + expression2.expression + ")");
  }

  FilterCompoundExpression FilterCompoundExpression::logical(FilterCompoundExpression expression1, FilterLogical operation, FilterCompoundExpression expression2) {
    return FilterCompoundExpression("(" + expression1.expression + mapLogical(operation) + expression2.expression + ")");
  }

  FilterCompoundExpression FilterCompoundExpression::logical(FilterExpression expression1, FilterLogical operation, FilterCompoundExpression expression2) {
    return FilterCompoundExpression("(" + expression1.expression + mapLogical(operation) + expression2.expression + ")");
  }

  FilterCompoundExpression FilterCompoundExpression::logical(FilterCompoundExpression expression1, FilterLogical operation, FilterExpression expression2) {
    return FilterCompoundExpression("(" + expression1.expression + mapLogical(operation) + expression2.expression + ")");
  }

  std::string FilterCompoundExpression::mapLogical(FilterLogical operation) {
    switch (operation) {
      case AND:
        return " AND ";
      case OR:
        return " OR ";
      case NOT:
        return " NOT ";
    }
  }
}