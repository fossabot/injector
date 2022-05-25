cmake_minimum_required(VERSION 3.22)
project(injector)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(injector
        src/main.cpp
        include/injector/injector.hpp
        include/injector/type_id.hpp
        src/type_id.cpp
        include/injector/factory.hpp
        include/injector/storage.hpp
        include/injector/provider.hpp include/injector/traits.hpp include/injector/errors.hpp src/errors.cpp)