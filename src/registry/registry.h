#pragma once

#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>

#include <sqlite3.h>

#include "types/registry_type.h"
#include "table/table_builder.h"
#include "table/table_schema.h"
#include "table/table_iterator.h"
#include "table/row/row_builder.h"

#include "exceptions/database_open_failure.h"
#include "exceptions/database_access_failure.h"

namespace iamaprogrammer {

  class Registry {
  public:
  
    Registry(std::filesystem::path databasePath);
    ~Registry();

    void addTable(std::string name, TableSchema* schema);
    TableIterator getTableIterator(std::string name);
    void dropTable(const std::string& tableName);

    RowBuilder addEntry(std::string table);
    void dropEntry(std::string table, std::string key);
    void dropEntry(std::string table, int key);
    void dropEntry(std::string table, double key);
    Row getEntry(std::string table, std::string key);
    Row getEntry(std::string table, int key);
    Row getEntry(std::string table, double key);

  private:
    sqlite3* db = nullptr;
    std::map<std::string, TableSchema*> schemas;
    const std::filesystem::path databasePath;
    //std::vector<V> entries;
  };
}