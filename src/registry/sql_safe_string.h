#pragma once
#include <string>
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace iamaprogrammer {
  class SqlSafeString {
    public:
      SqlSafeString(std::string str);
      SqlSafeString(const char* str);

      const std::string& toString();

    private:
      std::string str;
  };
}