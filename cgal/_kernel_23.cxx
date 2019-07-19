#include "_kernel_23.h"

// Move intersection types to template params
template<typename T1, typename T2>
py::object intersection (T1 a, T2 b) {
	auto result = CGAL::intersection(a, b);
	if(!result) 
		return py::cast<py::none>(Py_None);
	return boost::apply_visitor(PyCast_visitor(), *result);
}

template<typename T1, typename T2>
bool do_intersect (T1 p, T2 q) {
    return CGAL::do_intersect(p, q);
}

template<typename T1, typename T2>
void inline register_intersect(py::module &m)
{
    m.def("intersection", &intersection<T1, T2>);
    m.def("do_intersect", &do_intersect<T1, T2>);
}

PYBIND11_MODULE(_kernel_23, m)
{
    m.doc() = "Python binding of module Kernel_23";

    // -------------- Origin.h --------------
    py::class_<CGAL::Origin>(m, "_Origin");
    py::class_<CGAL::Null_vector>(m, "_Null_vector");
    m.attr("ORIGIN") = CGAL::ORIGIN;
    m.attr("NULL_VECTOR") = CGAL::NULL_VECTOR;

    // -------------- aff_transformation_tags.h --------------
	py::class_<CGAL::Rotation>(m, "_Rotation");
	py::class_<CGAL::Translation>(m, "_Translation");
	py::class_<CGAL::Scaling>(m, "_Scaling");
	py::class_<CGAL::Reflection>(m, "_Reflection");
    // XXX: py::class_<CGAL::Identity_transformation>(m, "_Identity_transformation");

	m.attr("ROTATION") = py::cast(CGAL::ROTATION);
	m.attr("TRANSLATION") = py::cast(CGAL::TRANSLATION);
	m.attr("SCALING") = py::cast(CGAL::SCALING);
	m.attr("REFLECTION") = py::cast(CGAL::REFLECTION);
    // XXX: m.attr("INDENTITY") = py::cast(CGAL::INDENTITY);

    // -------------- Point_2.h --------------
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
        .def("bbox", &Point_2::bbox)
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
        .def("__getitem__", &Point_2::operator[])
        .def("__str__", &cgal_str<Point_2>)
        .def("__repr__", &cgal_repr<Point_2>)
    ;

    // -------------- Vector_2.h --------------
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
        .def("direction", &Vector_2::direction)
        .def("perpendicular", &Vector_2::perpendicular)
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

    // -------------- Bbox_2.h --------------
    py::class_<Bbox_2>(m, "Bbox")
    	.def(py::init<>())
    	.def(py::init<double, double, double, double>(),
            py::arg("x_min"), py::arg("y_min"), py::arg("x_max"), py::arg("y_max"))
        .def_property_readonly("xmin", &Bbox_2::xmin)
        .def_property_readonly("ymin", &Bbox_2::ymin)
        .def_property_readonly("xmax", &Bbox_2::xmax)
        .def_property_readonly("ymax", &Bbox_2::ymax)
        .def_property_readonly("dimension", &Bbox_2::dimension)
        .def("max", &Bbox_2::max)
        .def("min", &Bbox_2::min)
        .def(py::self + Bbox_2())
        .def(py::self += Bbox_2())
        .def(py::self == Bbox_2())
        .def(py::self != Bbox_2())
        .def("__str__", &cgal_str<Bbox_2>)
        .def("__repr__", &cgal_repr<Bbox_2>)
    ;
    
    // -------------- Direction_2.h --------------
    py::class_<Direction_2>(m, "Direction_2")
        .def(py::init<Vector_2>())
        .def(py::init<Line_2>())
        .def(py::init<Ray_2>())
        .def(py::init<Segment_2>())
        .def(py::init<K::RT, K::RT>())
        .def("vector", &Direction_2::vector)
        .def("delta", &Direction_2::delta)
        .def("dx", &Direction_2::dx)
        .def("dy", &Direction_2::dy)
        .def("counterclockwise_in_between", &Direction_2::counterclockwise_in_between)
        .def("transform", &Direction_2::transform)
        .def(-py::self)
        .def(py::self == Direction_2())
        .def(py::self != Direction_2())
        .def(py::self <= Direction_2())
        .def(py::self >= Direction_2())
        .def(py::self < Direction_2())
        .def(py::self > Direction_2())
        .def("__str__", &cgal_str<Direction_2>)
        .def("__repr__", &cgal_repr<Direction_2>)
    ;

    // -------------- Segment_2.h --------------
    py::class_<Segment_2>(m, "Segment_2")
        .def(py::init<Point_2, Point_2>())
        .def_property_readonly("source", &Segment_2::source)
        .def_property_readonly("target", &Segment_2::target)
        .def_property_readonly("squared_length", &Segment_2::squared_length)
        .def("point", &Segment_2::point)
        .def("vertex", &Segment_2::vertex)
        .def_property_readonly("min", &Segment_2::min)
        .def_property_readonly("max", &Segment_2::max)
        .def("supporting_line", &Segment_2::supporting_line)
        .def("direction", &Segment_2::direction)
        .def("to_vector", &Segment_2::to_vector)
        .def("opposite", &Segment_2::opposite)
        .def_property_readonly("is_degenerate", &Segment_2::is_degenerate)
        .def_property_readonly("is_horizontal", &Segment_2::is_horizontal)
        .def_property_readonly("is_vertical", &Segment_2::is_vertical)
        .def("has_on", &Segment_2::has_on)
        .def("bbox", &Segment_2::bbox)
        .def("collinear_has_on", &Segment_2::collinear_has_on)
        .def("transform", &Segment_2::transform)
        .def(py::self == Segment_2())
        .def(py::self != Segment_2())
        .def("__str__", &cgal_str<Segment_2>)
        .def("__repr__", &cgal_repr<Segment_2>)
        .def("__getitem__", &Segment_2::operator[])
    ;

    // -------------- Line_2.h --------------
    py::class_<Line_2>(m, "Line_2")
    	.def(py::init<K::RT, K::RT, K::RT>(),
            py::arg("a"), py::arg("b"), py::arg("c"))
    	.def(py::init<Point_2, Point_2>())
    	.def(py::init<Point_2, Direction_2>())
    	.def(py::init<Point_2, Vector_2>())
    	.def(py::init<Segment_2>())
    	.def(py::init<Ray_2>())
        .def("to_vector", &Line_2::to_vector)
        .def_property_readonly("a", &Line_2::a)
        .def_property_readonly("b", &Line_2::b)
        .def_property_readonly("c", &Line_2::c)
        // XXX: .def("point", &Line_2::point)
        // XXX: .def("projection", &Point_2::projection)
        .def("x_at_y", &Line_2::x_at_y)
        .def("y_at_x", &Line_2::y_at_x)
        .def("to_vector", &Line_2::to_vector)
        .def_property_readonly("direction", &Line_2::direction)
        .def_property_readonly("opposite", &Line_2::opposite)
        .def("oriented_side", &Line_2::oriented_side)
        .def_property_readonly("perpendicular", &Line_2::perpendicular)
        .def("transform", &Line_2::transform)
        .def_property_readonly("is_horizontal", &Line_2::is_horizontal)
        .def_property_readonly("is_vertical", &Line_2::is_vertical)
        .def_property_readonly("is_degenerate", &Line_2::is_degenerate)
        .def("has_on", &Line_2::has_on)
        .def("has_on_positive_side", &Line_2::has_on_positive_side)
        .def("has_on_negative_side", &Line_2::has_on_negative_side)
        .def(py::self == Line_2())
        .def(py::self != Line_2())
        .def("__str__", &cgal_str<Segment_2>)
        .def("__repr__", &cgal_repr<Segment_2>)
    ;

    // -------------- Iso_rectangle_2.h --------------
    py::class_<Iso_rectangle_2>(m, "Iso_rectangle_2")
        .def(py::init<>())
        .def(py::init<Point_2, Point_2>())
        .def(py::init<Point_2, Point_2, int>())
        .def(py::init<Point_2, Point_2, Point_2, Point_2>(),
            py::arg("left"), py::arg("right"), py::arg("bottom"), py::arg("top"))
        .def(py::init<K::RT, K::RT, K::RT, K::RT>(),
            py::arg("min_hx"), py::arg("min_hy"), py::arg("max_hx"), py::arg("max_hy"))
        .def(py::init<K::RT, K::RT, K::RT, K::RT, K::RT>(),
            py::arg("min_hx"), py::arg("min_hy"), py::arg("max_hx"), py::arg("max_hy"), py::arg("hw"))
        .def(py::init<Bbox_2>())
        .def("vertex", &Iso_rectangle_2::vertex)
        .def_property_readonly("min", &Iso_rectangle_2::min)
        .def_property_readonly("max", &Iso_rectangle_2::max)
        .def_property_readonly("xmin", &Iso_rectangle_2::xmin)
        .def_property_readonly("xmax", &Iso_rectangle_2::xmax)
        .def_property_readonly("ymin", &Iso_rectangle_2::ymin)
        .def_property_readonly("ymax", &Iso_rectangle_2::ymax)
        .def_property_readonly("area", &Iso_rectangle_2::area)
        .def_property_readonly("bbox", &Iso_rectangle_2::bbox)
        .def("transform", &Iso_rectangle_2::transform)
        .def("min_coord", &Iso_rectangle_2::min_coord)
        .def("max_coord", &Iso_rectangle_2::max_coord)
        .def_property_readonly("is_degenerate", &Iso_rectangle_2::is_degenerate)
        .def("bounded_side", &Iso_rectangle_2::bounded_side)
        .def("has_on_boundary", &Iso_rectangle_2::has_on_boundary)
        .def("has_on_bounded_side", &Iso_rectangle_2::has_on_bounded_side)
        .def("has_on_unbounded_side", &Iso_rectangle_2::has_on_unbounded_side)
        .def(py::self == Iso_rectangle_2())
        .def(py::self != Iso_rectangle_2())
        .def("__str__", &cgal_str<Segment_2>)
        .def("__repr__", &cgal_repr<Segment_2>)
        .def("__getitem__", &Iso_rectangle_2::vertex)
    ;

    // -------------- Triangle_2.h --------------
    py::class_<Triangle_2>(m, "Triangle_2")
        .def(py::init<>())
        .def(py::init<Point_2, Point_2, Point_2>())
        .def("vertex", &Triangle_2::vertex)
        .def_property_readonly("area", &Triangle_2::area)
        .def_property_readonly("bbox", &Triangle_2::bbox)
        .def("transform", &Triangle_2::transform)
        .def_property_readonly("is_degenerate", &Triangle_2::is_degenerate)
        .def("bounded_side", &Triangle_2::bounded_side)
        .def("has_on_boundary", &Triangle_2::has_on_boundary)
        .def("has_on_bounded_side", &Triangle_2::has_on_bounded_side)
        .def("has_on_unbounded_side", &Triangle_2::has_on_unbounded_side)
        .def_property_readonly("orientation", &Triangle_2::orientation)
        .def("orientation_side", &Triangle_2::bounded_side)
        .def("has_on_negative_side", &Triangle_2::has_on_negative_side)
        .def("has_on_positive_side", &Triangle_2::has_on_unbounded_side)
        .def(py::self == Triangle_2())
        .def(py::self != Triangle_2())
        .def("__str__", &cgal_str<Segment_2>)
        .def("__repr__", &cgal_repr<Segment_2>)
        .def("__getitem__", &Triangle_2::vertex)
    ;

    // -------------- intersections.h --------------
    /* from Kernel_23/test/Kernel_23/include/CGAL/_test_all_linear_intersections.h
        test_2d<K1,K2>(iso_rectangle_2, iso_rectangle_2);
        test_2d<K1,K2>(iso_rectangle_2, line_2);
        test_2d<K1,K2>(iso_rectangle_2, ray_2);
        test_2d<K1,K2>(iso_rectangle_2, segment_2);
        test_2d<K1,K2>(iso_rectangle_2, triangle_2);
        test_2d<K1,K2>(line_2, line_2);
        test_2d<K1,K2>(line_2, ray_2);
        test_2d<K1,K2>(line_2, segment_2);
        test_2d<K1,K2>(line_2, triangle_2);
        test_2d<K1,K2>(ray_2, ray_2);
        test_2d<K1,K2>(ray_2, segment_2);
        test_2d<K1,K2>(ray_2, triangle_2);
        test_2d<K1,K2>(segment_2, segment_2);
        test_2d<K1,K2>(segment_2, triangle_2);
        test_2d<K1,K2>(triangle_2, triangle_2);

        test_3d<K1,K2>(line_3, line_3);
        test_3d<K1,K2>(line_3, plane_3);
        test_3d<K1,K2>(line_3, ray_3);
        test_3d<K1,K2>(line_3, segment_3);
        test_3d<K1,K2>(line_3, triangle_3);
        test_3d<K1,K2>(plane_3, plane_3);
        test_3d<K1,K2>(plane_3, ray_3);
        test_3d<K1,K2>(plane_3, segment_3);
        test_3d<K1,K2>(plane_3, sphere_3);
        test_3d<K1,K2>(plane_3, triangle_3);
        test_3d<K1,K2>(ray_3, ray_3);
        test_3d<K1,K2>(ray_3, segment_3);
        test_3d<K1,K2>(ray_3, triangle_3);
        test_3d<K1,K2>(segment_3, segment_3);
        test_3d<K1,K2>(segment_3, triangle_3);
        test_3d<K1,K2>(sphere_3, sphere_3);
        test_3d<K1,K2>(triangle_3, triangle_3);
    */
    register_intersect<Iso_rectangle_2, Iso_rectangle_2>(m);
    register_intersect<Iso_rectangle_2, Line_2>(m);
    register_intersect<Iso_rectangle_2, Ray_2>(m);
    register_intersect<Iso_rectangle_2, Segment_2>(m);
    register_intersect<Iso_rectangle_2, Triangle_2>(m);
    register_intersect<Line_2, Line_2>(m);
    register_intersect<Line_2, Ray_2>(m);
    register_intersect<Line_2, Segment_2>(m);
    register_intersect<Line_2, Triangle_2>(m);
    register_intersect<Ray_2, Ray_2>(m);
    register_intersect<Ray_2, Segment_2>(m);
    register_intersect<Ray_2, Triangle_2>(m);
    register_intersect<Segment_2, Segment_2>(m);
    register_intersect<Segment_2, Triangle_2>(m);
    register_intersect<Triangle_2, Triangle_2>(m);
}
