#include "row_builder.h"

namespace iamaprogrammer {
  RowBuilder::RowBuilder(sqlite3* db, SqlSafeString table) : db(db) {
    // Get column Count.
    sqlite3_stmt* columnStatement;
    if (sqlite3_prepare_v2(this->db, ("SELECT * FROM "+table.toString()+" LIMIT 1;").c_str(), -1, &columnStatement, nullptr) == SQLITE_OK) {
      this->columnCount = sqlite3_column_count(columnStatement);
      sqlite3_finalize(columnStatement);
    }

    // Create SQL insert statement for value binding.
    std::string columns = "";
    for (int index = 0; index < columnCount; index++) {
      if (columns.empty()) {
        columns += "?"+std::to_string(index+1);
      } else {
        columns += ", ?"+std::to_string(index+1);
      }
    }
    //std::cout << ("INSERT INTO "+table.toString()+" VALUES ("+columns+");") << std::endl;
    this->checkSQLErr(sqlite3_prepare_v2(this->db, ("INSERT INTO "+table.toString()+" VALUES ("+columns+");").c_str(), -1, &this->statement, nullptr));
  }

  RowBuilder::~RowBuilder() {
    sqlite3_step(statement);
    sqlite3_finalize(statement);
  }

  RowBuilder& RowBuilder::value(std::string value) {
    this->checkColumnMismatchErr();
    this->checkSQLErr(sqlite3_bind_text(this->statement, this->bindIndex, value.c_str(), -1, nullptr));
    this->bindIndex++;
    return *this;
  }

  RowBuilder& RowBuilder::value(int value) {
    this->checkColumnMismatchErr();
    this->checkSQLErr(sqlite3_bind_int(this->statement, this->bindIndex, value));
    this->bindIndex++;
    return *this;
  }

  RowBuilder& RowBuilder::value(double value) {
    this->checkColumnMismatchErr();
    this->checkSQLErr(sqlite3_bind_double(this->statement, this->bindIndex, value));
    this->bindIndex++;
    return *this;
  }

  RowBuilder& RowBuilder::null() {
    this->checkColumnMismatchErr();
    this->checkSQLErr(sqlite3_bind_null(this->statement, this->bindIndex));
    this->bindIndex++;
    return *this;
  }

  void RowBuilder::checkSQLErr(int err) {
    if (err != SQLITE_OK) {
      throw std::runtime_error("SQL Error: " + std::string(sqlite3_errstr(err)));
    }
  }

  void RowBuilder::checkColumnMismatchErr() {
    if (this->bindIndex > this->columnCount) {
      throw std::runtime_error("Value Error: Attempting to assign value to non-existent column.");
    }
  }
}