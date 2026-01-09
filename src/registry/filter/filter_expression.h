#pragma once
#include <string>

namespace iamaprogrammer {
  class Filter;
  class FilterCompoundExpression;

  enum FilterComparison {
    EQUALS,
    NOT_EQUALS,
    GREATER_THAN,
    GREATER_THAN_EQUAL_TO,
    LESS_THAN,
    LESS_THAN_EQUAL_TO
  };

  class FilterExpression {
    friend Filter;
    friend FilterCompoundExpression;

    public:
      static FilterExpression comparison(std::string name, FilterComparison operation, std::string type);
      static FilterExpression comparison(std::string name, FilterComparison operation, float type);
      static FilterExpression comparison(std::string name, FilterComparison operation, int type);
      static FilterExpression isNull(std::string name);
      //static FilterExpression isIn(std::string name, std::vector<>);

    private:
      std::string expression;

      FilterExpression(std::string expression);

      static std::string mapComparison(FilterComparison operation);
  };
}