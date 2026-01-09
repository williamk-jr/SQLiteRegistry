add_library(${PROJECT_NAME}
  registry/registry.cpp
  registry/value.cpp
  registry/sql_safe_string.cpp

  registry/filter/filter.cpp
  registry/filter/filter_expression.cpp
  registry/filter/filter_compound_expression.cpp

  registry/types/registry_type.cpp
  
  registry/exceptions/database_access_exception.cpp

  registry/table/table_schema.cpp
  registry/table/table_builder.cpp
  registry/table/table_iterator.cpp

  registry/table/row/row.cpp
  registry/table/row/row_builder.cpp
)

find_package(Sqlite3)

target_include_directories(${PROJECT_NAME} 
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(${PROJECT_NAME} sqlite3)
