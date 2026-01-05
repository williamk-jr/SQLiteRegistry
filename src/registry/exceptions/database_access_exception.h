#pragma once

#include <exception>
#include <string>

namespace iamaprogrammer {
  class DatabaseAccessException: public std::exception {
    public:
      DatabaseAccessException(std::string reason);

      virtual const char* what() const throw();
    private:
      std::string message;
  };
}