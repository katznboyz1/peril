cmake_minimum_required(VERSION 3.17)

set(PERIL_VERSION 0.1)

project(peril VERSION ${PERIL_VERSION})

set(lib_peril
    fetch_data_LANG_FR.cpp
    fetch_data_LANG_FR.hpp
)

add_executable(peril main.cpp)

add_library(lib_peril_lib ${lib_peril})

set_target_properties(lib_peril_lib PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(peril lib_peril_lib)

target_link_libraries(peril -lcurl)

set_target_properties(peril PROPERTIES COMPILE_OPTIONS "-O2;")