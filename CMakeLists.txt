cmake_minimum_required(VERSION 3.1)
project(spectre_bench CXX)

set( CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard whose features are requested.")

add_compile_definitions( UNICODE _UNICODE WINVER=0x0601 _WIN32_WINNT=0x0601 )

set( SOURCE_FOLDER "src" )

add_executable( spectre_bench WIN32 ${SOURCE_FOLDER}/SpectreBench.cpp )
