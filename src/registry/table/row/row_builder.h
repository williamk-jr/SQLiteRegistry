#pragma once
#include <string>
#include <vector>
#include <iostream>

#include <sqlite3.h>

#include "../../types/registry_type.h"
#include "../../sql_safe_string.h"

namespace iamaprogrammer {
  class Registry; // Forward Declaration

  class RowBuilder {
    friend iamaprogrammer::Registry;

    public:
      ~RowBuilder();

      RowBuilder(const RowBuilder&) = delete; // non construction-copyable
      RowBuilder& operator=(const RowBuilder&) = delete; // non copyable

      RowBuilder& value(std::string value);
      RowBuilder& value(int value);
      RowBuilder& value(double value);
      RowBuilder& null();

    private:
      sqlite3* db = nullptr;
      sqlite3_stmt* statement = nullptr;
      int columnCount = 0;
      int bindIndex = 1; // SQLite3 bind parameters start at index 1

      RowBuilder(sqlite3* db, SqlSafeString table);

      void checkSQLErr(int err);
      void checkColumnMismatchErr();
  };
}