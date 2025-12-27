#include "table.h"

namespace iamaprogrammer {

  Table::Table(sqlite3* db, TableSchema* schema, std::string name): db(db), schema(schema), name(name) {}

  RowBuilder Table::addRow() {
    return RowBuilder(this->db, this->name);
  }

  TableIterator Table::getIterator() {
    return TableIterator(this->db, this->name);
  }
  
  void Table::dropRowByIndex(const std::string& tableName, int index) {
    if (!this->db) {
      return;
    }

    std::string sql = "DELETE FROM " + tableName + " WHERE rowid = ?1;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
      return;
    }

    sqlite3_bind_int(stmt, 1, index);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cerr << "Failed to delete row from '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
    }
    sqlite3_finalize(stmt);
  }

  // Helper: find primary key column name for a table, empty if none
  static std::string findPrimaryKeyColumn(sqlite3* db, const std::string& tableName) {
    std::string pragma = "PRAGMA table_info(\"" + tableName + "\");";
    sqlite3_stmt* stmt = nullptr;
    std::string pkColumn;

    if (sqlite3_prepare_v2(db, pragma.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
      while (sqlite3_step(stmt) == SQLITE_ROW) {
        // columns: cid, name, type, notnull, dflt_value, pk
        int primaryKey = sqlite3_column_int(stmt, 5);

        if (primaryKey > 0) { // 0 means no colummn, otherwise, its the index of the column with primary key
          const unsigned char* text = sqlite3_column_text(stmt, 1);
          std::cout << text << std::endl;
          pkColumn = reinterpret_cast<const char*>(text);
          break;
        }
      }
    }
    if (stmt) {
      sqlite3_finalize(stmt);
    }
    return pkColumn;
  }

  void Table::dropRowByKey(const std::string& tableName, int key) {
    if (!this->db) {
      return;
    }

    std::string pk = findPrimaryKeyColumn(this->db, tableName);
    if (pk.empty()) {
      std::cerr << "No primary key found on table '" << tableName << "' — cannot delete by int key." << std::endl;
      return;
    }

    std::string sql = sql = "DELETE FROM \"" + tableName + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
      return;
    }

    sqlite3_bind_int(stmt, 1, key);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cerr << "Failed to delete row from '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
    }
    sqlite3_finalize(stmt);
  }

  void Table::dropRowByKey(const std::string& tableName, double key) {
    if (!this->db) {
      return;
    }

    std::string pk = findPrimaryKeyColumn(this->db, tableName);
    if (pk.empty()) {
      std::cerr << "No primary key found on table '" << tableName << "' — cannot delete by double key." << std::endl;
      return;
    }

    std::string sql = "DELETE FROM \"" + tableName + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
      return;
    }

    sqlite3_bind_double(stmt, 1, key);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cerr << "Failed to delete row from '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
    }
    sqlite3_finalize(stmt);
  }

  void Table::dropRowByKey(const std::string& tableName, const std::string& key) {
    if (!this->db) {
      return;
    };

    std::string pk = findPrimaryKeyColumn(this->db, tableName);
    if (pk.empty()) {
      std::cerr << "No primary key found on table '" << tableName << "' — cannot delete by string key." << std::endl;
      return;
    }

    std::string sql = "DELETE FROM \"" + tableName + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      std::cerr << "Failed to prepare delete statement for table '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
      return;
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      std::cerr << "Failed to delete row from '" << tableName << "': " << sqlite3_errmsg(this->db) << std::endl;
    }
    sqlite3_finalize(stmt);
  }

}