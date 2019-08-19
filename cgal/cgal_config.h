#ifndef CGAL_CYTHON_CONFIG_H
#define CGAL_CYTHON_CONFIG_H

// pybind11 check
#include <pybind11/pybind11.h>
#ifndef PYBIND11_MODULE
#error "PYBIND11 is not correctly included"
#endif

#include <pybind11/operators.h>

namespace py = pybind11;

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

// Helper functions and classes
#include <string>
#include <sstream>
template <typename T> inline std::string cgal_repr(const T & val)
{
    std::ostringstream ss;
    CGAL::set_pretty_mode(ss);
    ss << val;
    return ss.str();
}
template <typename T> inline std::string cgal_str(const T & val)
{
    std::ostringstream ss;
    ss << val;
    return ss.str();
}

template <typename T>
struct PySequenceIterator
{
    PySequenceIterator(const T & iter, const T & end, py::object ref)
        : iter(iter), end(end), ref(ref) {}
    py::object next()
    {
        if (iter == end)
            throw py::stop_iteration();
        return py::cast(*(iter++));
    }

    T iter, end;
    py::object ref; // keep a reference
    size_t index = 0;
    operator T() { return iter; }
};

template <typename T>
struct PySequenceCirculator
{
    PySequenceCirculator(const T & iter, py::object ref)
        : iter(iter), ref(ref) {}
    py::object next()
    {
        return py::cast(*(iter++));
    }

    T iter;
    py::object ref; // keep a reference
    size_t index = 0;
    operator T() { return iter; }
};

struct PyCast_visitor {
    typedef py::object result_type;
    template<typename T>
    result_type operator()(const T &t) const {
        return py::cast(t);
    }
};

#endif // CGAL_CYTHON_CONFIG_H
