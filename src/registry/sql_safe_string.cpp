#include "sql_safe_string.h"

namespace iamaprogrammer {
  SqlSafeString::SqlSafeString(std::string str) {
    bool isAlphanumeric = std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isalnum(c);
    });

    if (!isAlphanumeric) {
      throw std::runtime_error("String of value: \'" + str +"\' is sql-unsafe.");
    }
  }

  SqlSafeString::SqlSafeString(const char* str) : SqlSafeString(str) {}

  const std::string& SqlSafeString::toString() {
    return this->str;
  }
}