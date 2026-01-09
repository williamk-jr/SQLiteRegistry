#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include <filesystem>

#include "registry/registry.h"
#include "registry/filter/filter.h"
#include "registry/table/table_builder.h"

using namespace iamaprogrammer;

TEST_CASE("String primary key exists check") {
  Registry registry(std::filesystem::path(":memory:"));
  TableSchema schema = TableBuilder()
    .column("id", RegistryType::stringType())
    .column("value", RegistryType::integerType())
    .finish();

  registry.addTable("str_table", &schema);

  REQUIRE_FALSE(registry.hasEntry("str_table", std::string("key1")));

  registry.addEntry("str_table")
    .value(std::string("key1"))
    .value(123);

  REQUIRE(registry.hasEntry("str_table", std::string("key1")));

  Row r = registry.getEntry("str_table", std::string("key1"));
  REQUIRE(r["value"].asInteger() == 123);

  registry.dropEntry("str_table", std::string("key1"));
  REQUIRE_FALSE(registry.hasEntry("str_table", std::string("key1")));
}

TEST_CASE("Integer primary key exists check") {
  Registry registry(std::filesystem::path(":memory:"));
  TableSchema schema = TableBuilder()
    .column("id", RegistryType::integerType())
    .column("name", RegistryType::stringType())
    .finish();

  registry.addTable("int_table", &schema);

  REQUIRE_FALSE(registry.hasEntry("int_table", 42));

  registry.addEntry("int_table")
    .value(42)
    .value(std::string("the answer"));

  REQUIRE(registry.hasEntry("int_table", 42));

  Row r = registry.getEntry("int_table", 42);
  REQUIRE(r["name"].asString() == "the answer");

  registry.dropEntry("int_table", 42);
  REQUIRE_FALSE(registry.hasEntry("int_table", 42));
}

TEST_CASE("Double primary key exists check") {
  Registry registry(std::filesystem::path(":memory:"));
  TableSchema schema = TableBuilder()
    .column("id", RegistryType::floatType())
    .column("payload", RegistryType::stringType())
    .finish();

  registry.addTable("dbl_table", &schema);

  double key = 3.14;
  REQUIRE_FALSE(registry.hasEntry("dbl_table", key));

  registry.addEntry("dbl_table")
    .value(key)
    .value(std::string("pi"));

  REQUIRE(registry.hasEntry("dbl_table", key));

  Row r = registry.getEntry("dbl_table", key);
  REQUIRE(r["payload"].asString() == "pi");

  registry.dropEntry("dbl_table", key);
  REQUIRE_FALSE(registry.hasEntry("dbl_table", key));
}

TEST_CASE("Drop table removes schema") {
  Registry registry(std::filesystem::path(":memory:"));
  TableSchema schema = TableBuilder()
    .column("id", RegistryType::stringType())
    .column("v", RegistryType::integerType())
    .finish();

  registry.addTable("tmp", &schema);
  registry.addEntry("tmp").value(std::string("a")).value(1);

  REQUIRE(registry.hasEntry("tmp", std::string("a")));

  registry.dropTable("tmp");

  REQUIRE_THROWS_AS(registry.hasEntry("tmp", std::string("a")), std::out_of_range);
}

TEST_CASE("Ensure filters are constructed properly") {
  Filter filter = Filter(
    FilterExpression::comparison("testCol", FilterComparison::EQUALS, "testCol")
  );

  REQUIRE(filter.toSql() == "testCol == testCol");

  Filter compoundFilter = Filter(
    FilterCompoundExpression::logical(
      FilterExpression::comparison("test", FilterComparison::EQUALS, "test"), 
      FilterLogical::AND, 
      FilterExpression::comparison("test", FilterComparison::NOT_EQUALS, "non_test")
    )
  );

  REQUIRE(compoundFilter.toSql() == "(test == test AND test != non_test)");

  Filter compoundFilter2 = Filter(
    FilterCompoundExpression::logical(
      FilterCompoundExpression::logical(
        FilterExpression::comparison("test", FilterComparison::EQUALS, "test"),
        FilterLogical::OR,
        FilterExpression::comparison("test", FilterComparison::GREATER_THAN, 2)
      ), 
      FilterLogical::AND, 
      FilterExpression::comparison("test", FilterComparison::NOT_EQUALS, "non_test")
    )
  );

  REQUIRE(compoundFilter2.toSql() == "((test == test OR test > 2) AND test != non_test)");
}

TEST_CASE("Table iterator properly iterates table.") {
  Registry registry(std::filesystem::path(":memory:"));
  TableSchema schema = TableBuilder()
    .column("id", RegistryType::integerType())
    .column("value", RegistryType::integerType())
    .finish();

  registry.addTable("numbers", &schema);
  
  for (int i = 0; i < 10; i++) {
    registry.addEntry("numbers")
      .value(i)
      .value(i*2);
  }

  TableIterator iterator = registry.getTableIterator("numbers");
  while (iterator.next()) {
    Row row = iterator.row();
    int id = row["id"].asInteger();
    int value = row["value"].asInteger();

    REQUIRE(value == id*2);
  }
}

TEST_CASE("Table iterator properly iterates filtered table.") {
  Registry registry(std::filesystem::path(":memory:"));
  TableSchema schema = TableBuilder()
    .column("id", RegistryType::integerType())
    .column("value", RegistryType::integerType())
    .finish();

  registry.addTable("numbers", &schema);
  
  for (int i = 0; i < 10; i++) {
    registry.addEntry("numbers")
      .value(i)
      .value(i*2);
  }

  TableIterator iterator = registry.getTableIterator("numbers", Filter(
    FilterExpression::comparison("id", FilterComparison::GREATER_THAN, 5)
  ));
  
  while (iterator.next()) {
    Row row = iterator.row();
    int id = row["id"].asInteger();

    REQUIRE(id > 5);
  }
}