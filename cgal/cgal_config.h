#ifndef CGAL_CYTHON_CONFIG_H
#define CGAL_CYTHON_CONFIG_H

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
template <typename T> std::string to_string_op(const T & val)
{
    std::stringstream str;
    str << val;
    return str.str();
}

// Select types from kernel
typedef K::Point_2 Point_2;
typedef K::Vector_2 Vector_2;
typedef K::Segment_2 Segment_2;

#include <CGAL/Polygon_2.h>
template <typename Container_P=std::vector<CGAL::Polygon_2<K>::Point_2>>
using Polygon_2 = CGAL::Polygon_2<K, Container_P>;

#endif // CGAL_CYTHON_CONFIG_H
