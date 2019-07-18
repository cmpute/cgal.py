#include <cgal_config.h>

namespace py = pybind11;

typedef K::Point_2 Point_2;
typedef K::Vector_2 Vector_2;
typedef K::Segment_2 Segment_2;
typedef K::Ray_2 Ray_2;
typedef K::Line_2 Line_2;
// typedef K::Bbox_2 Bbox_2;

PYBIND11_MODULE(_kernel_23, m) {
    m.doc() = "Python binding of module Kernel_23";

    py::class_<CGAL::Origin>(m, "Origin");
    m.attr("ORIGIN") = CGAL::ORIGIN;
    py::class_<CGAL::Null_vector>(m, "Null_vector");
    m.attr("NULL_VECTOR") = CGAL::NULL_VECTOR;

    py::class_<Point_2>(m, "Point_2")
        .def(py::init<CGAL::Origin>(),
            py::doc("introduces a variable `p` with Cartesian coordinates (0,0)"))
        .def(py::init<K::FT, K::FT>(), py::arg("x"), py::arg("y"),
            py::doc("introduces a point `p` initialized to `(x,y)`"))
        .def(py::init<K::RT, K::RT, K::RT>(), py::arg("hx"), py::arg("hy"), py::arg("hw")=K::RT(1),
            py::doc("introduces a point `p` initialized to `(hx/hw,hy/hw)`"))
        .def_property_readonly("x", &Point_2::x)
        .def_property_readonly("y", &Point_2::y)
        .def_property_readonly("hx", &Point_2::hx)
        .def_property_readonly("hy", &Point_2::hy)
        .def_property_readonly("hw", &Point_2::hw)
        .def_property_readonly("dimension", &Point_2::dimension)
        .def("cartesian", &Point_2::cartesian)
        .def("homogeneous", &Point_2::homogeneous)
        .def(py::self == Point_2())
        .def(py::self != Point_2())
        .def(py::self < Point_2())
        .def(py::self > Point_2())
        .def(py::self <= Point_2())
        .def(py::self >= Point_2())
        .def(py::self - Point_2())
        .def(py::self += Vector_2())
        .def(py::self -= Vector_2())
        .def(py::self + Vector_2())
        .def(py::self - Vector_2())
        .def(py::self - CGAL::Origin())
        // .def("bbox", &Point_2::bbox)
        .def("__getitem__", &Point_2::operator[])
        .def("__str__", &cgal_str<Point_2>)
        .def("__repr__", &cgal_repr<Point_2>)
    ;
    py::class_<Vector_2>(m, "Vector_2")
        .def(py::init<CGAL::Null_vector>(), py::doc("introduces a null vector `v`"))
        .def(py::init<K::FT, K::FT>(), py::arg("x"), py::arg("y"),
            py::doc("introduces a vector `v` initialized to `(x,y)`"))
        .def(py::init<K::RT, K::RT, K::RT>(), py::arg("hx"), py::arg("hy"), py::arg("hw")=K::RT(1),
            py::doc("introduces a vector `v` initialized to `(hx/hw,hy/hw)`"))
    	.def(py::init<Point_2, Point_2>(), py::arg("a"), py::arg("b"),
            py::doc("introduces the vector `b-a`"))
        .def(py::init<Ray_2>(), py::arg("l"),
            py::doc("introduces the vector having the same direction as `l`"))
        .def(py::init<Segment_2>())
        .def(py::init<Line_2>())
        .def_property_readonly("squared_length", &Vector_2::squared_length)
        // .def("direction", &Vector_2::direction)
        // .def("perpendicular", &Vector_2::perpendicular)
        .def("cartesian", &Vector_2::cartesian)
        .def_property_readonly("x", &Vector_2::x)
        .def_property_readonly("y", &Vector_2::y)
        .def_property_readonly("hx", &Vector_2::hx)
        .def_property_readonly("hy", &Vector_2::hy)
        .def_property_readonly("hw", &Vector_2::hw)
        .def_property_readonly("squared_length", &Vector_2::squared_length)
        .def(py::self == Vector_2())
        .def(py::self != Vector_2())
        .def(py::self + Vector_2())
        .def(py::self += Vector_2())
        .def(py::self - Vector_2())
        .def(py::self -= Vector_2())
        .def(py::self * Vector_2())
        .def(py::self *= K::FT())
        .def(K::FT() * py::self)
        .def(py::self * K::FT())
        .def(K::RT() * py::self)
        .def(py::self * K::RT())
        .def(py::self / K::FT())
        .def(py::self /= K::FT())
        .def(-py::self)
        .def("__str__", &cgal_str<Vector_2>)
        .def("__repr__", &cgal_repr<Vector_2>)
    ;
}
