cmake_minimum_required(VERSION 3.17)

set(PERIL_VERSION 0.1)

project(peril VERSION ${PERIL_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 1)

set(CMAKE_CXX_FLAGS_RELEASE -O2)

set(lib_peril
    fetch_data_LANG_FR.cpp
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

add_library(lib_peril_lib ${lib_peril})
add_library(lib_curl_lib ${lib_curl})

add_executable(peril main.cpp)

set_target_properties(lib_peril_lib PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lib_curl_lib PROPERTIES LINKER_LANGUAGE C)

target_link_libraries(peril lib_peril_lib)
target_link_libraries(peril lib_curl_lib)

install(TARGETS peril DESTINATION peril-${PERIL_VERSION})