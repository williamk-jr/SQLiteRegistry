#pragma once
#include <string>
#include "filter_expression.h"
#include "filter_compound_expression.h"

namespace iamaprogrammer {
  class Filter {
    public:
      Filter();
      Filter(FilterExpression expression);
      Filter(FilterCompoundExpression expression);

      std::string toSql();
      bool isEmpty();
      
    private:
      std::string expression;
  };
}