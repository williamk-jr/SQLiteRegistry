#include "table_builder.h"

namespace iamaprogrammer {
  TableBuilder::TableBuilder() {

  }

  TableBuilder& TableBuilder::column(std::string label, RegistryType type) {
    this->columnTypes.push_back({label, type});
    this->columnTypeMap[label] = this->columnTypes.size()-1;
    return *this;
  }


  TableSchema TableBuilder::finish() {
    return TableSchema(this->columnTypes, this->columnTypeMap);
  }

  // TableBuilder::TableBuilder(sqlite3* db, std::string name) : db(db), name(name) {}

  // TableBuilder& TableBuilder::column(std::string label, RegistryType type) {
  //   return this->column(label, type, false);
  // }

  // TableBuilder& TableBuilder::column(std::string label, RegistryType type, bool primaryKey) {
  //   std::string column = label + " " + type.getSqlType();

  //   if (!primaryKey) {
  //     this->sql.push_back(column);
  //     return *this;
  //   }
    
  //   this->sql.push_back(column + " PRIMARY KEY");
  //   return *this;
  // }

  // void TableBuilder::finish() {
  //   std::string columns = "";

  //   for (std::string column : this->sql) {
  //     if (columns.empty()) {
  //       columns += column;
  //     } else {
  //       columns += ", " + column;
  //     }
  //   }
  //   std::cout << columns << std::endl;

  //   if (this->db) {
  //     sqlite3_stmt* stmt;
  //     int err = 0;

  //     err = sqlite3_prepare_v2(this->db, ("CREATE TABLE IF NOT EXISTS " + this->name + " (" + columns + ");").c_str(), -1, &stmt, nullptr);
  //     err = sqlite3_bind_text(stmt, 1, this->name.c_str(), -1, SQLITE_STATIC);
  //     err = sqlite3_step(stmt);
  //     err = sqlite3_finalize(stmt);
  //   }
  // }
}