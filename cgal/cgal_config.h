#ifndef CGAL_CYTHON_CONFIG_H
#define CGAL_CYTHON_CONFIG_H

// pybind11 check
#include <pybind11/pybind11.h>
#ifndef PYBIND11_MODULE
#error "PYBIND11 is not correctly included"
#endif

#include <pybind11/operators.h>

/*

Since the CGAL is highly templated, we need to specify Kernel type
to manually expand type traits. However, the ability to change kernel
type is reserved.

*/

// Kernel selection
#if defined USE_CGAL_KERNEL_EPIC
    #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
#elif defined USE_CGAL_KERNEL_EPEC
    #include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
    typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
#elif defined USE_CGAL_KERNEL__
    // TODO: Other kernels...
    #error "Custom Kernel needs manual editing of this header."
#else
    #error "Unrecognized CGAL kernel"
#endif

// Helper functions
#include <string>
#include <sstream>
template <typename T> inline std::string to_string_cgal(const T & val)
{
    std::ostringstream ss;
    CGAL::set_pretty_mode(ss);
    ss << val;
    return ss.str();
}

// Forward definitions
void init_kernel_23(pybind11::module &m);

#endif // CGAL_CYTHON_CONFIG_H
