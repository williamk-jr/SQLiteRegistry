#pragma once

#include <exception>
#include <string>

namespace iamaprogrammer {
  class ColumnNotFoundException: public std::exception {
    public:
      ColumnNotFoundException(std::string columnName);

      virtual const char* what() const throw();
    private:
      std::string message;
  };
}