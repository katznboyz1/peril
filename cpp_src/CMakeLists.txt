cmake_minimum_required(VERSION 3.17)

project(peril LANGUAGES CXX C VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(CMAKE_CXX_FLAGS_RELEASE -O2)

set(src
    fetch_data_LANG_FR.cpp
)

set(lib
    fetch_data_LANG_FR.hpp
)

add_library(imported_libraries ${src} ${lib})

add_executable(peril main.cpp)

add_subdirectory(libcurl_headers)

target_link_libraries(peril imported_libraries)
target_link_libraries(peril libcurl_h)