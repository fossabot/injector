cmake_minimum_required(VERSION 3.15)

project(injector VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        include/injector/detail/argument_resolver.hpp
        include/injector/detail/factory.hpp
        include/injector/detail/provider.hpp
        include/injector/detail/storage.hpp

        include/injector/injector.hpp
        include/injector/type_id.hpp        src/type_id.cpp
        include/injector/traits.hpp
        include/injector/errors.hpp         src/errors.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(test)