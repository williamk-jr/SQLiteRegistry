#include "registry_type.h"



namespace iamaprogrammer {

  RegistryType::RegistryType(std::string sqlType) : sql(sqlType) {}

  RegistryType RegistryType::stringType() {
    return RegistryType("TEXT");
  }
  
  RegistryType RegistryType::integerType() {
    return RegistryType("INTEGER");
  }
  
  RegistryType RegistryType::floatType() {
    return RegistryType("REAL");
  }
  
  RegistryType RegistryType::blobType() {
    return RegistryType("BLOB");
  }
  
  RegistryType RegistryType::nullType() {
    return RegistryType("NULL");
  }

  std::string RegistryType::getSqlType() const {
    return this->sql;
  }
}
