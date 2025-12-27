#pragma once
#include <string>
#include <vector>
#include <iostream>

#include <sqlite3.h>

#include "../types/registry_type.h"
#include "row/row_builder.h"
#include "table_iterator.h"
#include "table_schema.h"

namespace iamaprogrammer {
  class Registry; // Forward Declaration

  class Table {
    friend iamaprogrammer::Registry;

    public:
      RowBuilder addRow();
      TableIterator getIterator();
      
      void dropRowByIndex(const std::string& tableName, int index);
      void dropRowByKey(const std::string& tableName, int key);
      void dropRowByKey(const std::string& tableName, double key);
      void dropRowByKey(const std::string& tableName, const std::string& key);

    private:
      sqlite3* db = nullptr;
      TableSchema* schema = nullptr;
      std::string name;

      Table(sqlite3* db, TableSchema* schema, std::string name);
  };
}