#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <memory>

#include <sqlite3.h>

#include "table_schema.h"
#include "../types/registry_type.h"
#include "row/row.h"

namespace iamaprogrammer {
  class Registry; // Forward Declaration

  class TableIterator {
    friend iamaprogrammer::Registry;

    // Implement

    public:
      ~TableIterator();

      bool next();
      Row row();

    private:
      TableSchema* schema = nullptr;
      sqlite3_stmt* statement = nullptr;
      int status = 0;

      TableIterator(sqlite3* db, const std::string &tableName, TableSchema* schema);
  };
}