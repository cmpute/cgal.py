find_package(CGAL REQUIRED COMPONENTS Core)

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

include_directories(${CGAL_INCLUDE_DIRS})
link_directories(${CGAL_LIBRARY_DIRS})
add_definitions(${CGAL_DEFINITIONS})

# Add at last to make sure using the right python library
include_directories(BEFORE ${PYTHON_INCLUDE_DIR})

# support cython/c api
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_cython_target(_kernel_23 CXX)
add_library(_kernel_23 MODULE ${_kernel_23})
target_link_libraries(_kernel_23 CGAL::CGAL)
python_extension_module(_kernel_23)
install(TARGETS _kernel_23 LIBRARY DESTINATION cgal)
