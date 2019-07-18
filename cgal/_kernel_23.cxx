#include <cgal_config.h>

namespace py = pybind11;

typedef K::Point_2 Point_2;
typedef K::Vector_2 Vector_2;
typedef K::Segment_2 Segment_2;

void init_kernel_23(py::module &fm) {
    py::module m = fm.def_submodule("_kernel_23",
        "Python binding of module Kernel_23");

    py::class_<Point_2>(m, "Point_2")
        .def(py::init())
        .def(py::init<K::FT, K::FT>())
        .def(py::init<K::RT, K::RT, K::RT>())
        .def_property_readonly("x", &Point_2::x)
        .def_property_readonly("y", &Point_2::y)
        .def_property_readonly("hx", &Point_2::hx)
        .def_property_readonly("hy", &Point_2::hy)
        .def_property_readonly("hw", &Point_2::hw)
        .def("__str__", &to_string_cgal<Point_2>)
    ;
    py::class_<Vector_2>(m, "Vector_2") 
    	.def(py::init<Point_2, Point_2>())
        // .def(py::init<Ray_2>())
        .def(py::init<Segment_2>())
        // .def(py::init<Line_2>())
        .def_property_readonly("squared_length", &Vector_2::squared_length)
        // .def("direction", &Vector_2::direction)
        // .def("perpendicular", &Vector_2::perpendicular)
        .def("cartesian", &Vector_2::cartesian)
        .def_property_readonly("x", &Vector_2::x)
        .def_property_readonly("y", &Vector_2::y)
        .def_property_readonly("hx", &Vector_2::hx)
        .def_property_readonly("hy", &Vector_2::hy)
        .def_property_readonly("hw", &Vector_2::hw)
        .def(py::self * double())
        .def(py::self + Vector_2())
        .def(py::self - Vector_2())
        .def(double() * py::self)
        .def(py::self / double())
        .def(-py::self)
        .def("__str__", &to_string_cgal<Vector_2>)
    ;
}
