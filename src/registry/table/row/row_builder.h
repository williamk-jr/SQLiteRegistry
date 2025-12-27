#pragma once
#include <string>
#include <vector>
#include <iostream>

#include <sqlite3.h>

#include "../../types/registry_type.h"

namespace iamaprogrammer {
  class Registry; // Forward Declaration

  class RowBuilder {
    friend iamaprogrammer::Registry;

    public:
      RowBuilder& value(std::string value);
      RowBuilder& value(int value);
      RowBuilder& value(double value);
      RowBuilder& null();

      void finish();

    private:
      sqlite3* db = nullptr;
      sqlite3_stmt* statement = nullptr;
      int columnCount = 0;
      int index = 1; // SQLite3 bind parameters start at index 1

      RowBuilder(sqlite3* db, std::string tableName);

      void checkSQLErr(int err);
      void checkColumnMismatchErr();
  };
}