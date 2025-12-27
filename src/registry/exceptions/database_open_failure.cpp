#include "database_open_failure.h"

namespace iamaprogrammer {
  DatabaseOpenFailureException::DatabaseOpenFailureException(std::string reason): 
    message("Failed to open database: "+reason) {}

  const char* DatabaseOpenFailureException::what() const throw() {
    return this->message.c_str();
  }
}