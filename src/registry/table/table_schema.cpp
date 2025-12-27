#include "table_schema.h"

namespace iamaprogrammer {
  TableSchema::TableSchema(std::vector<std::pair<std::string, RegistryType>> columnTypes, std::map<std::string, size_t> columnTypeMap): 
    columnTypes(columnTypes), columnTypeMap(columnTypeMap) {}

  const std::pair<std::string, RegistryType>& TableSchema::get(int index) const {
    return this->columnTypes.at(index);
  }

  const std::pair<std::string, RegistryType>& TableSchema::get(std::string columnName) const {
    return this->columnTypes.at(this->columnTypeMap.at(columnName));
  }

  size_t TableSchema::indexOf(std::string columnName) const {
    return this->columnTypeMap.at(columnName);
  }

  bool TableSchema::contains(std::string columnName) const {
    return this->columnTypeMap.find(columnName) != this->columnTypeMap.end();
  }

  size_t TableSchema::columnCount() {
    return this->columnTypes.size();
  }
}