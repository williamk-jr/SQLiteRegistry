#include <iostream>
#include <filesystem>
#include "registry/registry.h"

int main() {
  std::filesystem::path dbPath("./test.db");

  if (std::filesystem::exists(dbPath) && std::filesystem::remove(dbPath)) {
    std::cout << "succesfully removed database" << std::endl;
  }

  iamaprogrammer::Registry registry(dbPath);
  iamaprogrammer::TableSchema schema = iamaprogrammer::TableBuilder()
    .column("id", iamaprogrammer::RegistryType::stringType())
    .column("value", iamaprogrammer::RegistryType::integerType())
    .finish();

  registry.addTable("test_table", &schema);

  // iamaprogrammer::Table table = registry.getTable("test_table");

  registry.addEntry("test_table")
    .value("test_id")
    .value(67)
    .finish();

  registry.addEntry("test_table")
    .value("test_id2")
    .value(69)
    .finish();

  iamaprogrammer::TableIterator iterator = registry.getTableIterator("test_table");
  
  while (iterator.next()) {
    iamaprogrammer::Row row = iterator.row();
    iamaprogrammer::Value id = row["id"];
    iamaprogrammer::Value value = row["value"];

    std::cout << id.asString() << ", " << value.asInteger() << std::endl;
  }


  iamaprogrammer::Row testRow = registry.getEntry("test_table", "test_id2");
  iamaprogrammer::Value testId = testRow["value"];
  std::cout << testId.asInteger() << std::endl;

  //test.dropRowByIndex("test_table", 2);
  //table.dropRowByKey("test_table", "test_id2");
  return 0;
}
