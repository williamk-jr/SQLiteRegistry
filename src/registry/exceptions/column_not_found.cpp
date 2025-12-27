#include "column_not_found.h"

namespace iamaprogrammer {
  ColumnNotFoundException::ColumnNotFoundException(std::string columnName): 
    message("Could not find column of name \""+columnName+"\".") {}

  const char* ColumnNotFoundException::what() const throw() {
    return this->message.c_str();
  }
}