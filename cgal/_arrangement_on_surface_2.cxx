#include "_arrangement_on_surface_2.h"
#include "_kernel_23.h"

Segment_polyline_traits_2 segment_polyline_traits;
Segment_polyline_traits_2::Construct_curve_2 segment_polyline_constructor = segment_polyline_traits.construct_curve_2_object();

PYBIND11_MODULE(_arrangement_on_surface_2, m)
{
    m.doc() = "Python binding of module Arrangement_on_surface_2";

    // reference https://doc.cgal.org/latest/Arrangement_on_surface_2/classCGAL_1_1Arr__segment__traits__2.html
    py::implicitly_convertible<Segment_polyline_traits_2::Segment_2, Segment_2>();

    py::class_<Polyline_2>(m, "Polyline_2")
        .def(py::init<>())
	    .def("__init__", [](Polyline_2& base, std::vector<Point_2> points) {
            new (&base) Polyline_2(points.begin(), points.end());
        })
	    .def("__init__", [](Polyline_2& base, std::vector<Segment_2> segments) {
            new (&base) Polyline_2(segments.begin(), segments.end());
        })
        .def("__str__", &cgal_str<Polyline_2>)
        .def("__repr__", &cgal_repr<Polyline_2>)
    ;
}
