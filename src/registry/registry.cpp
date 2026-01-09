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

  void Registry::addTable(SqlSafeString table, TableSchema* schema) {
    this->ensureDatabase();

    // Preform SQLite table creation operation.
    std::string sql = "CREATE TABLE IF NOT EXISTS " + table.toString() + " (" + schema->toSql() + ");";
    sqlite3_stmt* stmt;

    int err = 0;
    err = sqlite3_prepare_v2(this->db, sql.c_str(), -1, &stmt, nullptr);
    err = sqlite3_bind_text(stmt, 1, table.toString().c_str(), -1, SQLITE_STATIC);
    err = sqlite3_step(stmt);
    err = sqlite3_finalize(stmt);

    this->schemas[table.toString()] = schema;
  }

  TableIterator Registry::getTableIterator(SqlSafeString table) {
    return this->getTableIterator(table, Filter(), -1);
  }

  TableIterator Registry::getTableIterator(SqlSafeString table, Filter entryFilter) {
    return this->getTableIterator(table, entryFilter, -1);
  }

  TableIterator Registry::getTableIterator(SqlSafeString table, Filter entryFilter, int count) {
    return TableIterator(this->db, table, this->schemas[table.toString()], entryFilter, count);
  }

  void Registry::dropTable(SqlSafeString table) {
    this->ensureDatabase();

    std::string sql = "DROP TABLE IF EXISTS \"" + table.toString() + "\";";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (this->schemas.find(table.toString()) != this->schemas.end()) {
      this->schemas.erase(table.toString());
    }
  }

  RowBuilder Registry::addEntry(SqlSafeString table) {
    return RowBuilder(this->db, table);
  }

  void Registry::dropEntry(SqlSafeString table, std::string key) {
    this->ensureDatabase();

    std::string pk = this->getPrimaryColumn(table);
    std::string sql = "DELETE FROM \"" + table.toString() + "\" WHERE \"" + pk + "\" = ?;";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      throw DatabaseAccessException("Failed to delete row from '" + table.toString() + "': " + sqlite3_errmsg(this->db));
    }
    sqlite3_finalize(stmt);
  }

  void Registry::dropEntry(SqlSafeString table, int key) {
    this->ensureDatabase();

    std::string pk = this->getPrimaryColumn(table);
    std::string sql = "DELETE FROM \"" + table.toString() + "\" WHERE \"" + pk + "\" = ?;";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_bind_int(stmt, 1, key);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      throw DatabaseAccessException("Failed to delete row from '" + table.toString() + "': " + sqlite3_errmsg(this->db));
    }
    sqlite3_finalize(stmt);
  }

  void Registry::dropEntry(SqlSafeString table, double key) {
    this->ensureDatabase();

    std::string pk = this->getPrimaryColumn(table);
    std::string sql = "DELETE FROM \"" + table.toString() + "\" WHERE \"" + pk + "\" = ?;";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_bind_double(stmt, 1, key);
    if (sqlite3_step(stmt) != SQLITE_DONE) {
      throw DatabaseAccessException("Failed to delete row from '" + table.toString() + "': " + sqlite3_errmsg(this->db));
    }
    sqlite3_finalize(stmt);
  }

  Row Registry::getEntry(SqlSafeString table, std::string key) {
    return Row(this->db, table, key, this->schemas[table.toString()]);
  }

  Row Registry::getEntry(SqlSafeString table, int key) {
    return Row(this->db, table, key, this->schemas[table.toString()]);
  }

  Row Registry::getEntry(SqlSafeString table, double key) {
    return Row(this->db, table, key, this->schemas[table.toString()]);
  }

  bool Registry::hasEntry(SqlSafeString table, std::string key) {
    this->ensureDatabase();

    std::string pk = this->getPrimaryColumn(table);
    std::string sql = "SELECT 1 FROM \"" + table.toString() + "\" WHERE \"" + pk + "\" = ?;";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_bind_text(stmt, 1, key.c_str(), -1, SQLITE_TRANSIENT);
    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW;
  }

  bool Registry::hasEntry(SqlSafeString table, int key) {
    this->ensureDatabase();

    std::string pk = this->getPrimaryColumn(table);
    std::string sql = "SELECT 1 FROM \"" + table.toString() + "\" WHERE \"" + pk + "\" = ?;";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_bind_int(stmt, 1, key);
    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW;
  }

  bool Registry::hasEntry(SqlSafeString table, double key) {
    this->ensureDatabase();

    std::string pk = this->getPrimaryColumn(table);
    std::string sql = "SELECT 1 FROM \"" + table.toString() + "\" WHERE \"" + pk + "\" = ?;";

    sqlite3_stmt* stmt = nullptr;
    this->prepare(sql, &stmt);

    sqlite3_bind_double(stmt, 1, key);
    int step = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return step == SQLITE_ROW;
  }

  std::vector<std::string> Registry::getTableNames() {
    std::vector<std::string> keys;
    for (std::map<std::string, TableSchema*>::iterator iter = this->schemas.begin(); iter != this->schemas.end(); iter++) {
      keys.push_back(iter->first);
    }

    return keys;
  }

  // Helper Functions

  void Registry::prepare(const std::string& sql, sqlite3_stmt** stmt) {
    if (sqlite3_prepare_v2(this->db, sql.c_str(), -1, stmt, nullptr) != SQLITE_OK) {
      throw DatabaseAccessException("Failed to prepare statement: " + std::string(sqlite3_errmsg(this->db)));
    }
  }

  void Registry::ensureDatabase() {
    if (!this->db) {
      throw DatabaseAccessException("Database does not exist.");
    } 
  }

  std::string Registry::getPrimaryColumn(SqlSafeString table) {
    const std::string& pk = this->schemas.at(table.toString())->get(0).first;
    if (pk.empty()) {
      throw DatabaseAccessException("No primary key found on table '" + table.toString() + "' — cannot check by double key.");
    }
    return pk;
  }
}