#include "database_access_exception.h"

namespace iamaprogrammer {
  DatabaseAccessException::DatabaseAccessException(std::string reason): 
    message("Failed to access database: "+reason) {}

  const char* DatabaseAccessException::what() const throw() {
    return this->message.c_str();
  }
}