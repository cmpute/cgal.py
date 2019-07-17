#include <cgal_config.h>

// typedef K::Point_2 Point_2;
// typedef K::Vector_2 Vector_2;
// typedef K::Segment_2 Segment_2;

// #include <CGAL/Polygon_2.h>
// template <typename Container_P=std::vector<CGAL::Polygon_2<K>::Point_2>>
// using Polygon_2 = CGAL::Polygon_2<K, Container_P>;

namespace py = pybind11;

PYBIND11_MODULE(_kernel_23, m) {
    m.doc() = "Python binding of module Kernel_23";

    py::class_<K::Point_2>(m, "Point_2")
        .def(py::init())
        .def(py::init<K::FT, K::FT>())
        .def(py::init<K::RT, K::RT, K::RT>())
        .def_property_readonly("x", &Point::x)
        .def_property_readonly("y", &Point::y)
        .def_property_readonly("hx", &Point::hx)
        .def_property_readonly("hy", &Point::hy)
        .def_property_readonly("hw", &Point::hw)
    ;
    py::class_<Vector_2>(m, "Vector") 
    	.def(py::init<Point_2, Point_2>())
        .def(py::init<Ray_2>())
        .def(py::init<Segment_2>())
        .def(py::init<Line_2>())
        .def("squared_length", &Vector_2::squared_length)
        .def("direction", &Vector_2::direction)
        .def("perpendicular", &Vector_2::perpendicular)
        .def("cartesian", &Vector_2::cartesian)
        .def_property_readonly("x", &Point::x)
        .def_property_readonly("y", &Point::y)
        .def_property_readonly("hx", &Point::hx)
        .def_property_readonly("hy", &Point::hy)
        .def_property_readonly("hw", &Point::hw)
        .def(py::self * double())
        .def(py::self + Vector_2())
        .def(py::self - Vector_2())
        .def(double() * py::self)
        .def(py::self / double())
        .def(-py::self)
        .def("__repr__", &toString<Vector_2>)
    ;
}
