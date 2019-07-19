#include "_surface_sweep_2.h"
#include "_kernel_23.h"

template <typename Curve>
std::vector<Point_2> compute_intersection_points(std::vector<Curve> curves, bool report_endpoints)
{
    std::vector<Point_2> points;
    CGAL::compute_intersection_points(curves.begin(), curves.end(), std::back_inserter(pts));
    return points;
}

template <typename Curve>
std::vector<Curve> compute_subcurves(std::vector<Curve> curves, bool mult_overlaps)
{
    std::vector<Curve> subcurves;
    CGAL::compute_subcurves(curves.begin(), curves.end(), std::back_inserter(subcurves));
    return subcurves;
}

template <typename Curve>
bool do_curves_intersect(std::vector<Curve> curves)
{
    return CGAL::do_curves_intersect(curves.begin(), curves.end());
}

PYBIND11_MODULE(_surface_sweep_2, m)
{
    m.doc() = "Python binding of module Surface_sweep_2";

    m.def("compute_intersection_points", &compute_intersection_points<Segment_2>,
        py::arg("curves"), py::arg("report_endpoints") = false);
    m.def("compute_subcurves", &compute_subcurves<Segment_2>,
        py::arg("curves"), py::arg("mult_overlaps") = false);
    m.def("do_curves_intersect", &do_curves_intersect<Segment_2>,
        py::arg("curves");
}
