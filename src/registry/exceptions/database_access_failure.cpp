#include "database_access_failure.h"

namespace iamaprogrammer {
  DatabaseAccessFailureException::DatabaseAccessFailureException(std::string reason): 
    message("Failed to access database: "+reason) {}

  const char* DatabaseAccessFailureException::what() const throw() {
    return this->message.c_str();
  }
}