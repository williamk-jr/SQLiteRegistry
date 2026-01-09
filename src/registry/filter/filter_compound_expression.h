#pragma once
#include <string>
#include "filter_expression.h"

namespace iamaprogrammer {
  class Filter;

  enum FilterLogical {
    AND,
    OR,
    NOT
  };

  class FilterCompoundExpression {
    friend Filter;

    public:
      static FilterCompoundExpression logical(FilterExpression expression1, FilterLogical operation, FilterExpression expression2);
      static FilterCompoundExpression logical(FilterCompoundExpression expression1, FilterLogical operation, FilterCompoundExpression expression2);
      static FilterCompoundExpression logical(FilterExpression expression1, FilterLogical operation, FilterCompoundExpression expression2);
      static FilterCompoundExpression logical(FilterCompoundExpression expression1, FilterLogical operation, FilterExpression expression2);

    private:
      std::string expression;

      FilterCompoundExpression(std::string expression);
      
      static std::string mapLogical(FilterLogical operation);
  };
}