include(GoogleTest)

add_executable(injector-test
        injector_with_function.cpp)

target_link_libraries(injector-test gtest gtest_main injector)

gtest_discover_tests(injector-test)