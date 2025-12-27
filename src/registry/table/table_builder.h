#pragma once
#include <string>
#include <vector>
#include <iostream>

#include <sqlite3.h>

#include "../types/registry_type.h"
#include "table_schema.h"

namespace iamaprogrammer {
  class Registry; // Forward Declaration

  class TableBuilder {
    friend iamaprogrammer::Registry;

    public:
      TableBuilder();

      TableBuilder& column(std::string label, RegistryType type);

      TableSchema finish();

    private:
      std::vector<std::pair<std::string, RegistryType>> columnTypes;
      std::map<std::string, size_t> columnTypeMap;
      // sqlite3* db = nullptr;
      // std::vector<std::string> sql;
      // std::string name;
  };
}