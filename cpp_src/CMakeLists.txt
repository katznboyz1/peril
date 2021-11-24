cmake_minimum_required(VERSION 3.17)

set(PERIL_VERSION 0.1)

project(peril VERSION ${PERIL_VERSION})

set(src
    fetch_data_LANG_FR.cpp
    fetch_data_LANG_FR.hpp

    stdfunctions.cpp
    stdfunctions.hpp
)

add_executable(peril main.cpp)

add_library(source ${src})

set_target_properties(source PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(peril source)

target_link_libraries(peril -lcurl)

set_target_properties(peril PROPERTIES COMPILE_OPTIONS "-O2;")