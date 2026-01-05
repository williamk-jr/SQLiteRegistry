add_subdirectory(lib/Catch2)

add_executable(tests)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)