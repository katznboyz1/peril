cmake_minimum_required(VERSION 3.17)

project(peril LANGUAGES CXX C VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(CMAKE_CXX_FLAGS_RELEASE -O2)

set(src
    fetch_data_LANG_FR.cpp
)

set(lib_peril
    fetch_data_LANG_FR.hpp
)

set(lib_curl
    curlver.h
    easy.h
    libcurl.h
    mprintf.h
    multi.h
    options.h
    stdcheaders.h
    system.h
    typecheck-gcc.h
    urlapi.h
)

add_library(lib_peril_lib ${src} ${lib_peril_lib})
add_library(lib_curl_lib ${lib_curl})

add_executable(peril main.cpp)

target_link_libraries(peril lib_peril_lib lib_curl_lib)