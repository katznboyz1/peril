cmake_minimum_required(VERSION 3.17)

project(peril LANGUAGES CXX C VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(src
    fetch_data_LANG_FR.cpp
)

set(lib
    fetch_data_LANG_FR.hpp

    lib/curl.h
    lib/curlver.h
    lib/easy.h
    lib/multi.h
    lib/options.h
    lib/system.h
    lib/urlapi.h
)

add_library(imported_libraries ${lib} ${src})

add_executable(peril main.cpp)

target_link_libraries(peril imported_libraries)