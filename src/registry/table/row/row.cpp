#include "row.h"

namespace iamaprogrammer {
  Row::Row(sqlite3* db, SqlSafeString table, std::string key, TableSchema* schema): schema(schema), hasOwnership(true) {
    std::string pk = this->schema->get(0).first;
    std::string sql = "SELECT * FROM "+table.toString()+" WHERE "+pk+" = ?1;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &this->statement, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << table.toString() << "': " << sqlite3_errmsg(db) << std::endl;
      return;
    }

    sqlite3_bind_text(this->statement, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(this->statement) != SQLITE_ROW) {
      std::cerr << "Failed to retrieve entry from '" << table.toString() << "': " << sqlite3_errmsg(db) << std::endl;
    }
  }

  Row::Row(sqlite3* db, SqlSafeString table, int key, TableSchema* schema): schema(schema), hasOwnership(true) {
    std::string pk = this->schema->get(0).first;
    std::string sql = "SELECT * FROM "+table.toString()+" WHERE "+pk+" = ?1;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &this->statement, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << table.toString() << "': " << sqlite3_errmsg(db) << std::endl;
      return;
    }

    sqlite3_bind_int(this->statement, 1, key);
    if (sqlite3_step(this->statement) != SQLITE_ROW) {
      std::cerr << "Failed to retrieve entry from '" << table.toString() << "': " << sqlite3_errmsg(db) << std::endl;
    }
  }

  Row::Row(sqlite3* db, SqlSafeString table, double key, TableSchema* schema): schema(schema), hasOwnership(true) {
    std::string pk = this->schema->get(0).first;
    std::string sql = "SELECT * FROM "+table.toString()+" WHERE "+pk+" = ?1;";

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &this->statement, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << table.toString() << "': " << sqlite3_errmsg(db) << std::endl;
      return;
    }

    sqlite3_bind_double(this->statement, 1, key);
    if (sqlite3_step(this->statement) != SQLITE_ROW) {
      std::cerr << "Failed to retrieve entry from '" << table.toString() << "': " << sqlite3_errmsg(db) << std::endl;
    }
  }

  Row::Row(sqlite3_stmt* statement, TableSchema* schema): statement(statement), schema(schema) {}

  Row::~Row() {
    if (hasOwnership) sqlite3_finalize(this->statement);
  }
}