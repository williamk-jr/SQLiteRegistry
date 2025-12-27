#pragma once
#include <string>

namespace iamaprogrammer {
  class RegistryType {
    public:
      static RegistryType stringType();
      static RegistryType integerType();
      static RegistryType floatType();
      static RegistryType blobType();
      static RegistryType nullType();

      std::string getSqlType() const;
      bool isPrimaryKey() const;
    private:
      RegistryType(std::string sqlType);

      std::string sql;
  };
}

// STRING_TYPE,
// INTEGER_TYPE,
// FLOAT_TYPE,
// BLOB_TYPE,
// NULL_TYPE,