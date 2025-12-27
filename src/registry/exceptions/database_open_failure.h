#pragma once

#include <exception>
#include <string>

namespace iamaprogrammer {
  class DatabaseOpenFailureException: public std::exception {
    public:
      DatabaseOpenFailureException(std::string reason);

      virtual const char* what() const throw();
    private:
      std::string message;
  };
}