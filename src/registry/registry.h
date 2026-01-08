#pragma once

#include <filesystem>
#include <functional>
#include <iostream>
#include <memory>

#include <sqlite3.h>

#include "sql_safe_string.h"
#include "types/registry_type.h"
#include "table/table_builder.h"
#include "table/table_schema.h"
#include "table/table_iterator.h"
#include "table/row/row_builder.h"

#include "exceptions/database_access_exception.h"

namespace iamaprogrammer {

  class Registry {
  public:
  
    Registry(std::filesystem::path databasePath);
    ~Registry();

    void addTable(SqlSafeString name, TableSchema* schema);
    TableIterator getTableIterator(SqlSafeString name);
    void dropTable(SqlSafeString tableName);

    RowBuilder addEntry(SqlSafeString table);
    
    void dropEntry(SqlSafeString table, std::string key);
    void dropEntry(SqlSafeString table, int key);
    void dropEntry(SqlSafeString table, double key);

    Row getEntry(SqlSafeString table, std::string key);
    Row getEntry(SqlSafeString table, int key);
    Row getEntry(SqlSafeString table, double key);

    bool hasEntry(SqlSafeString table, std::string key);
    bool hasEntry(SqlSafeString table, int key);
    bool hasEntry(SqlSafeString table, double key);

  private:
    sqlite3* db = nullptr;
    std::map<std::string, TableSchema*> schemas;
    const std::filesystem::path databasePath;

    void prepare(const std::string& sql, sqlite3_stmt** stmt);
    std::string getPrimaryColumn(SqlSafeString table);
    void ensureDatabase();
    //std::vector<V> entries;
  };
}