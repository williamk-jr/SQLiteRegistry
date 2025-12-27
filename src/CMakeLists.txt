add_executable(${PROJECT_NAME} main.cpp
  registry/registry.cpp
  registry/value.cpp

  registry/types/registry_type.cpp

  registry/exceptions/column_not_found.cpp
  registry/exceptions/database_open_failure.cpp
  registry/exceptions/database_access_failure.cpp

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
