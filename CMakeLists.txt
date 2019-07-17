cmake_minimum_required(VERSION 3.5.0)

project(cgal_pybind11)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# ----------- Find required packages --------------

add_subdirectory(pybind11)
find_package(PythonExtensions REQUIRED)
find_package(NumPy REQUIRED)

# Add at last to make sure using the right python library
include_directories(BEFORE ${PYTHON_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR}/cgal)
include_directories(${NumPy_INCLUDE_DIRS})
include_directories(${pybind11_INCLUDE_DIRS})

find_package(CGAL REQUIRED COMPONENTS Core)
include_directories(${CGAL_INCLUDE_DIRS})
include_directories(${CGAL_INCLUDE_DIRS})
link_directories(${CGAL_LIBRARY_DIRS})
add_definitions(${CGAL_DEFINITIONS})

# ----------- Options ------------

# VALID options would be
# C: Cartesian
# EPIC: Exact_predicates_inexact_constructions_kernel
# EPEC: Exact_predicates_exact_constructions_kernel
# EPECR: Exact_predicates_exact_constructions_kernel_with_root_of
# EPECS: Exact_predicates_exact_constructions_kernel_with_sqrt
# EPECKR: Exact_predicates_exact_constructions_kernel_with_kth_root
# _: Custom kernels
set(CGAL_KERNEL "EPIC" CACHE STRING "Select Kernel for CGAL instantiation")
add_definitions(-DUSE_CGAL_KERNEL_${CGAL_KERNEL})

# ----------- Modules compilation ----------
pybind11_add_module(_kernel_23 cgal/_kernel_23.cxx)
install(TARGETS _kernel_23 LIBRARY DESTINATION cgal)

