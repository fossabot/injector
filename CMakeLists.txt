cmake_minimum_required(VERSION 3.15)

project(injector VERSION 1.0.0 LANGUAGES CXX)

option(INJECTOR_RUN_TESTS "Run tests" OFF)

set(CMAKE_CXX_STANDARD 17)

if (INJECTOR_RUN_TESTS)
    include(FetchContent)
    FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_subdirectory(test)
endif()


add_library(${PROJECT_NAME} STATIC
        include/injector/injector.hpp
        include/injector/type_id.hpp        src/type_id.cpp
        include/injector/factory.hpp
        include/injector/storage.hpp
        include/injector/provider.hpp
        include/injector/traits.hpp
        include/injector/errors.hpp         src/errors.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)