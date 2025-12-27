#include "table_iterator.h"

namespace iamaprogrammer {
  TableIterator::TableIterator(sqlite3* db, const std::string &tableName, TableSchema* schema): schema(schema) {
    std::string sql = "SELECT * FROM " + tableName + ";";
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &this->statement, nullptr) != SQLITE_OK) {
      std::cout << "not fine" << std::endl;
    }
    //this->status = sqlite3_step(this->statement);
  }

  TableIterator::~TableIterator() {
    sqlite3_finalize(this->statement);
  }

  bool TableIterator::next() {
    if (sqlite3_step(this->statement) != SQLITE_ROW) {
      return false;
    }
    return true;
  }

  Row TableIterator::row() {
    return Row(this->statement, this->schema);
  }

  // Map column names to their indicies.
    // std::string columnNameSql = "PRAGMA table_info("+tableName+");";
    // sqlite3_stmt* columnNameStatement = nullptr;
    // if (sqlite3_prepare_v2(db, columnNameSql.c_str(), -1, &columnNameStatement, nullptr) != SQLITE_OK) {

    // }
    // int index = 0;
    // while (sqlite3_step(columnNameStatement) == SQLITE_ROW) {
    //   std::string columnName = reinterpret_cast<const char*>(sqlite3_column_text(columnNameStatement, 1));
    //   this->columnNames[columnName] = index;
    //   index++;
    // }
    // sqlite3_finalize(columnNameStatement);
}