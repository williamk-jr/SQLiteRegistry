#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "../types/registry_type.h"

namespace iamaprogrammer {
  class TableBuilder;

  class TableSchema {
    friend iamaprogrammer::TableBuilder;

    public:
      size_t columnCount();
      const std::pair<std::string, RegistryType>& get(int index) const;
      const std::pair<std::string, RegistryType>& get(std::string index) const;
      size_t indexOf(std::string columnName) const;
      bool contains(std::string columnName) const;

      std::string toSql();

    private:
      const std::vector<std::pair<std::string, RegistryType>> columnTypes;
      const std::map<std::string, size_t> columnTypeMap;

      TableSchema(std::vector<std::pair<std::string, RegistryType>> columnTypes, std::map<std::string, size_t> columnTypeMap);
  };
}