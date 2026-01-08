add_executable(tests registry_tests.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain registry)

include(CTest)
add_test(NAME registry_tests COMMAND tests)