cmake_minimum_required(VERSION 3.15)
project(SpeexAEC)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(pybind11 REQUIRED)

aux_source_directory(speex/src SPEEX_SRC)
aux_source_directory(src AEC_SRC)

add_library(speexaec SHARED ${SPEEX_SRC})
target_compile_definitions(speexaec PUBLIC -DFLOATING_POINT PUBLIC -DHAVE_CONFIG_H)
target_include_directories(speexaec PUBLIC speex/include)

add_library(speexaec-static STATIC ${SPEEX_SRC})
target_compile_definitions(speexaec-static PUBLIC -DFLOATING_POINT PUBLIC -DHAVE_CONFIG_H)
target_include_directories(speexaec-static PUBLIC speex/include)

add_library(echocanceller SHARED ${AEC_SRC})
target_compile_definitions(echocanceller PUBLIC -DFLOATING_POINT PUBLIC -DNO_PYBIND11)
target_include_directories(echocanceller PUBLIC speex/include)
target_link_libraries(echocanceller PUBLIC speexaec-static)

add_executable(Main main.cpp)
target_link_libraries(Main PUBLIC echocanceller)

pybind11_add_module(pyspeexaec py_module.cpp ${AEC_SRC} ${SPEEX_SRC})
target_include_directories(pyspeexaec PUBLIC speex/include)
target_compile_definitions(pyspeexaec PUBLIC -DFLOATING_POINT -DHAVE_CONFIG_H)