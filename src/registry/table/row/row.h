#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <sqlite3.h>

#include "../table_schema.h"

#include "../../types/registry_type.h"
#include "../../value.h"

#include "../../exceptions/column_not_found.h"

namespace iamaprogrammer {
  class Registry; // Forward Declaration
  class TableIterator;

  class Row {
    friend iamaprogrammer::Registry;
    friend iamaprogrammer::TableIterator;

    // Create value type using c++ variants
    public:
      ~Row();

      const Value operator[](std::string column) const {
        if (!this->schema->contains(column)) {
          throw ColumnNotFoundException(column);
        }

        int type = sqlite3_column_type(this->statement, this->schema->indexOf(column));
        switch (type) {
          case SQLITE_TEXT:
            return Value(reinterpret_cast<const char*>(sqlite3_column_text(this->statement, this->schema->indexOf(column))));
          case SQLITE_INTEGER:
            return Value(sqlite3_column_int(this->statement, this->schema->indexOf(column)));
          case SQLITE_FLOAT:
            return Value(sqlite3_column_double(this->statement, this->schema->indexOf(column)));
          default:
            return Value();
        }
      }

    private:
      TableSchema* schema = nullptr;
      sqlite3_stmt* statement = nullptr;
      bool hasOwnership = false;

      Row(sqlite3* db, std::string table, std::string key, TableSchema* schema);
      Row(sqlite3* db, std::string table, int key, TableSchema* schema);
      Row(sqlite3* db, std::string table, double key, TableSchema* schema);
      Row(sqlite3_stmt* statement, TableSchema* schema);
  };
}