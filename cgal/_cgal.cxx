#include <cgal_config.h>

namespace py = pybind11;

PYBIND11_MODULE(cgal, m)
{
    m.doc() = "Python wrapper of CGAL with pybind11";
    init_kernel_23(m);
}
