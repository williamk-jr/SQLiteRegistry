#pragma once

#include <exception>
#include <string>

namespace iamaprogrammer {
  class DatabaseAccessFailureException: public std::exception {
    public:
      DatabaseAccessFailureException(std::string reason);

      virtual const char* what() const throw();
    private:
      std::string message;
  };
}