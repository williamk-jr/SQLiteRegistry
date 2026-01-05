#include "registry.h"

namespace iamaprogrammer {
  Registry::Registry(std::filesystem::path databasePath) : databasePath(databasePath) {
    if (sqlite3_open(this->databasePath.c_str(), &this->db) != SQLITE_OK) {
      throw DatabaseAccessException(sqlite3_errmsg(this->db));
      this->db = nullptr;
    }
  }

  Registry::~Registry() {
    // if (!this->db) {
    //   throw DatabaseAccessFailureException("Database does not exist.");
    // }
    sqlite3_close(this->db);
  }

  void Registry::addTable(std::string name, TableSchema* schema) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    }

    // Create SQL column descriptors.
    std::string columns = "";
    for (int i = 0; i < schema->columnCount(); i++) {
      const std::pair<std::string, RegistryType>& columnSchema = schema->get(i);
      std::string column = columnSchema.first + " " + columnSchema.second.getSqlType();
      if (i == 0) {
        column += " PRIMARY KEY";
      }

      if (columns.empty()) {
        columns += column;
      } else {
        columns += ", " + column;
      }
    }

    // Preform SQLite table creation operation.
    sqlite3_stmt* stmt;
    int err = 0;
    err = sqlite3_prepare_v2(this->db, ("CREATE TABLE IF NOT EXISTS " + name + " (" + columns + ");").c_str(), -1, &stmt, nullptr);
    err = sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_STATIC);
    err = sqlite3_step(stmt);
    err = sqlite3_finalize(stmt);

    this->schemas[name] = schema;
  }

  TableIterator Registry::getTableIterator(std::string name) {
    return TableIterator(this->db, name, this->schemas[name]);
  }

  void Registry::dropTable(const std::string& tableName) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    }
    std::string sql = "DROP TABLE IF EXISTS \"" + tableName + "\";";
    sqlite3_stmt* stmt = nullptr;
    char* err = nullptr;

    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to drop table '" + tableName + "': " + (err ? err : "unknown"));
    }

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (this->schemas.find(tableName) != this->schemas.end()) {
      this->schemas.erase(tableName);
    }
  }

  RowBuilder Registry::addEntry(std::string table) {
    return RowBuilder(this->db, table);
  }

  void Registry::dropEntry(std::string table, std::string key) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    };

    std::string pk = this->schemas.at(table)->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table + "' — cannot delete by string key.");
    }

    std::string sql = "DELETE FROM \"" + table + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare delete statement for table '" + table + "': " + sqlite3_errmsg(this->db));
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      throw DatabaseAccessException("Failed to delete row from '" + table + "': " + sqlite3_errmsg(this->db));
    }
    sqlite3_finalize(stmt);
  }

  void Registry::dropEntry(std::string table, int key) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    };

    std::string pk = this->schemas.at(table)->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table + "' — cannot delete by string key.");
    }

    std::string sql = "DELETE FROM \"" + table + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare delete statement for table '" + table + "': " + sqlite3_errmsg(this->db));
    }

    sqlite3_bind_int(stmt, 1, key);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      throw DatabaseAccessException("Failed to delete row from '" + table + "': " + sqlite3_errmsg(this->db));
    }
    sqlite3_finalize(stmt);
  }

  void Registry::dropEntry(std::string table, double key) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    };

    std::string pk = this->schemas.at(table)->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table + "' — cannot delete by string key.");
    }

    std::string sql = "DELETE FROM \"" + table + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare delete statement for table '" + table + "': " + sqlite3_errmsg(this->db));
    }

    sqlite3_bind_double(stmt, 1, key);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      throw DatabaseAccessException("Failed to delete row from '" + table + "': " + sqlite3_errmsg(this->db));
    }
    sqlite3_finalize(stmt);
  }

  Row Registry::getEntry(std::string table, std::string key) {
    return Row(this->db, table, key, this->schemas[table]);
  }

  Row Registry::getEntry(std::string table, int key) {
    return Row(this->db, table, key, this->schemas[table]);
  }

  Row Registry::getEntry(std::string table, double key) {
    return Row(this->db, table, key, this->schemas[table]);
  }

  bool Registry::hasEntry(std::string table, std::string key) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    }

    std::string pk = this->schemas.at(table)->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table + "' — cannot check by string key.");
    }

    std::string sql = "SELECT 1 FROM \"" + table + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare select statement for table '" + table + "': " + sqlite3_errmsg(this->db));
    }

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW;
  }

  bool Registry::hasEntry(std::string table, int key) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    }

    std::string pk = this->schemas.at(table)->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table + "' — cannot check by integer key.");
    }

    std::string sql = "SELECT 1 FROM \"" + table + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare select statement for table '" + table + "': " + sqlite3_errmsg(this->db));
    }

    sqlite3_bind_int(stmt, 1, key);
    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW;
  }

  bool Registry::hasEntry(std::string table, double key) {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    }

    std::string pk = this->schemas.at(table)->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table + "' — cannot check by double key.");
    }

    std::string sql = "SELECT 1 FROM \"" + table + "\" WHERE \"" + pk + "\" = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare select statement for table '" + table + "': " + sqlite3_errmsg(this->db));
    }

    sqlite3_bind_double(stmt, 1, key);
    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW;
  }

}