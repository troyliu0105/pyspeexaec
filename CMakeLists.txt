cmake_minimum_required(VERSION 3.15)
project(SpeexAEC)

set(CMAKE_CXX_STANDARD 11)

find_package(pybind11 REQUIRED)

aux_source_directory(speex/src SPEEX_SRC)
aux_source_directory(src AEC_SRC)

add_library(speexaec SHARED ${AEC_SRC} ${SPEEX_SRC})
target_compile_definitions(speexaec PUBLIC -DFLOATING_POINT -DHAVE_CONFIG_H)
target_link_directories(speexaec PUBLIC libspeexdsp)
target_include_directories(speexaec PUBLIC speex/include)

add_executable(Main main.cpp)
target_link_libraries(Main PUBLIC speexaec)

pybind11_add_module(pyspeexaec py_module.cpp ${AEC_SRC} ${SPEEX_SRC})
target_include_directories(pyspeexaec PUBLIC speex/include)
target_compile_definitions(pyspeexaec PUBLIC -DFLOATING_POINT -DHAVE_CONFIG_H)