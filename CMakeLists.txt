cmake_minimum_required(VERSION 3.5.0)

project(cgal_cython)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(PythonExtensions REQUIRED)
find_package(Cython REQUIRED)
find_package(NumPy REQUIRED)
include_directories(${NumPy_INCLUDE_DIRS})

if(SETUP_TEST)
    add_subdirectory(test)
else()
    add_subdirectory(cgal)
endif()
