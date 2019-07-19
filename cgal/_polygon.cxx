#include "_polygon.h"
#include "_kernel_23.h"

namespace py = pybind11;

PYBIND11_MODULE(_polygon, m)
{
    m.doc() = "Python wrapper of module Polygon";

    // We need use iterator to insert values. So we don't use py::make_iterator
    typedef PySequenceIterator<Polygon_2::Vertex_iterator> PyVertexIterator;
    typedef PySequenceIterator<Polygon_2::Edge_const_iterator> PyEdgeIterator;
    typedef PySequenceCirculator<Polygon_2::Vertex_circulator> PyVertexCirculator;
    typedef PySequenceCirculator<Polygon_2::Edge_const_circulator> PyEdgeCirculator;
    typedef PySequenceIterator<Polygon_with_holes_2::Hole_iterator> PyHoleIterator;

    // -------------- Polygon_2.h --------------
    py::class_<Polygon_2>(m, "Polygon_2")
        .def(py::init<>())
	    .def("__init__", [](Polygon_2& base, std::vector<Point_2> vertices) {
            new (&base) Polygon_2(vertices.begin(), vertices.end());
        })
        .def_property_readonly("vertices", [](py::object self) {
            return PyVertexIterator(
                self.cast<const Polygon_2 &>().vertices_begin(), 
                self.cast<const Polygon_2 &>().vertices_end(), 
                self); 
        }, py::return_value_policy::copy, py::doc("Returns a constant iterator that allows to traverse the vertices of the polygon"))
        .def_property_readonly("vertices_circulator", [](py::object self) { 
            return PyVertexCirculator(
                self.cast<const Polygon_2 &>().vertices_circulator(),
                self);
        }, py::return_value_policy::copy, py::doc("Returns a mutable circulator that allows to traverse the vertices of the polygon."))
        .def_property_readonly("edges", [](py::object self) { 
            return PyEdgeIterator(
                self.cast<const Polygon_2 &>().edges_begin(), 
                self.cast<const Polygon_2 &>().edges_end(), 
                self); 
        }, py::return_value_policy::copy, py::doc("Returns a non-mutable iterator that allows to traverse the edges of the polygon."))
        .def_property_readonly("edges_circulator", [](py::object self) { 
            return PyEdgeCirculator(
                self.cast<const Polygon_2 &>().edges_circulator(),
                self);
        }, py::return_value_policy::copy, py::doc("Returns a non-mutable circulator that allows to traverse the edges of the polygon."))

        // std::vector-like operators
        .def("push_back", &Polygon_2::push_back)
        .def("set", [](Polygon_2& base, PyVertexIterator &iter, Point_2 &p) {
            base.set(iter.iter, p);
        })
        .def("insert", [](Polygon_2& base, PyVertexIterator &iter, Point_2 &p) {
            base.insert(iter.iter, p);
        })
        .def("insert", [](Polygon_2& base, PyVertexIterator &iter, std::vector<Point_2> vertices) {
            base.insert(iter.iter, vertices.begin(), vertices.end());
        })
        .def("erase", [](Polygon_2& base, PyVertexIterator &iter) {
            base.erase(iter.iter);
        })
        .def("erase", [](Polygon_2& base, PyVertexIterator &begin, PyVertexIterator &end) {
            base.erase(begin.iter, end.iter);
        })
        .def("clear", &Polygon_2::clear)
        .def_property_readonly("is_empty", &Polygon_2::is_empty)

        // list-like operators
        .def("append", &Polygon_2::push_back)
    	.def("__len__", &Polygon_2::size)

        // indexers
        .def("vertex", &Polygon_2::vertex)
        .def("__getitem__", &Polygon_2::operator[])
        .def("edge", &Polygon_2::edge)

        // properties
        .def("reverse_orientation", &Polygon_2::reverse_orientation)
    	.def_property_readonly("is_simple", &Polygon_2::is_simple)
    	.def_property_readonly("is_convex", &Polygon_2::is_convex)
    	.def("orientation", &Polygon_2::orientation)
    	.def("bbox", &Polygon_2::bbox)
    	.def("area", &Polygon_2::area)
    	.def_property_readonly("is_counterclockwise_oriented", &Polygon_2::is_counterclockwise_oriented)
    	.def_property_readonly("is_clockwise_oriented", &Polygon_2::is_clockwise_oriented)
    	.def_property_readonly("is_collinear_oriented", &Polygon_2::is_collinear_oriented)
    	.def("left_vertex", [](py::object self){
            return PyVertexIterator(
                self.cast<const Polygon_2 &>().left_vertex(),
                self.cast<const Polygon_2 &>().vertices_end(),
                self);
        })
    	.def("right_vertex", [](py::object self){
            return PyVertexIterator(
                self.cast<const Polygon_2 &>().right_vertex(),
                self.cast<const Polygon_2 &>().vertices_end(),
                self);
        })
    	.def("top_vertex", [](py::object self){
            return PyVertexIterator(
                self.cast<const Polygon_2 &>().top_vertex(),
                self.cast<const Polygon_2 &>().vertices_end(),
                self);
        })
    	.def("bottom_vertex", [](py::object self){
            return PyVertexIterator(
                self.cast<const Polygon_2 &>().bottom_vertex(),
                self.cast<const Polygon_2 &>().vertices_end(),
                self);
        })
    	.def("has_on_positive_side", &Polygon_2::has_on_positive_side)
    	.def("has_on_negative_side", &Polygon_2::has_on_negative_side)
    	.def("has_on_boundary", &Polygon_2::has_on_boundary)
    	.def("has_on_bounded_side", &Polygon_2::has_on_bounded_side)
    	.def("has_on_unbounded_side", &Polygon_2::has_on_unbounded_side)
        .def("__str__", &cgal_str<Polygon_2>)
        .def("__repr__", &cgal_repr<Polygon_2>)
        .def(py::self == Polygon_2())
        .def(py::self != Polygon_2())
    ;

    // -------------- Polygon_with_holes_2.h --------------
    py::class_<Polygon_with_holes_2>(m, "Polygon_with_holes")
        .def(py::init<>())
        .def(py::init<Polygon_2>())
	    .def("__init__", [](Polygon_with_holes_2& base, Polygon_2& pgn_boundary, std::vector<Polygon_2> holes) {
            new (&base) Polygon_with_holes_2(pgn_boundary, holes.begin(), holes.end());
        })
        .def("outer_boundary", [](const Polygon_with_holes_2 & p) -> Polygon_2 {
            return p.outer_boundary();
        })
        .def_property_readonly("holes", [](py::object self) { 
            return PyHoleIterator(
                self.cast<Polygon_with_holes_2 &>().holes_begin(), 
                self.cast<Polygon_with_holes_2 &>().holes_end(), 
                self
            ); 
        })
        .def("add_hole", &Polygon_with_holes_2::add_hole)
        .def("erase_hole", [](Polygon_with_holes_2& base, PyHoleIterator &iter) {
            base.erase_hole(iter.iter);
        })
        .def("clear", &Polygon_with_holes_2::clear)
        .def_property_readonly("has_holes", &Polygon_with_holes_2::has_holes)
    	.def_property_readonly("is_unbounded", &Polygon_with_holes_2::is_unbounded)
    	.def_property_readonly("is_plane", &Polygon_with_holes_2::is_plane)
    	.def_property_readonly("number_of_holes", &Polygon_with_holes_2::number_of_holes)
    	.def("bbox", &Polygon_with_holes_2::bbox)
        .def("__str__", &cgal_str<Polygon_with_holes_2>)
        .def("__repr__", &cgal_repr<Polygon_with_holes_2>)
    ;

    py::class_<PyVertexIterator>(m, "Vertex_iterator")
        .def("__iter__", [](PyVertexIterator &it) -> PyVertexIterator& { return it; })
        .def("__next__", &PyVertexIterator::next);
    py::class_<PyEdgeIterator>(m, "Edge_const_iterator")
        .def("__iter__", [](PyEdgeIterator &it) -> PyEdgeIterator& { return it; })
        .def("__next__", &PyEdgeIterator::next);
    py::class_<PyVertexCirculator>(m, "Vertex_circulator")
        .def("__iter__", [](PyVertexCirculator &it) -> PyVertexCirculator& { return it; })
        .def("__next__", &PyVertexCirculator::next);
    py::class_<PyEdgeCirculator>(m, "Edge_const_circulator")
        .def("__iter__", [](PyEdgeCirculator &it) -> PyEdgeCirculator& { return it; })
        .def("__next__", &PyEdgeCirculator::next);
    py::class_<PyHoleIterator>(m, "Hole_iterator")
        .def("__iter__", [](PyHoleIterator &it) -> PyHoleIterator& { return it; })
        .def("__next__", &PyHoleIterator::next);
}