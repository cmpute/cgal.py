from libcpp cimport bool

cdef extern from "CGAL/Surface_sweep_2_algorithms.h" namespace "CGAL" nogil:
    OutputIterator compute_intersection_points[InputIterator, OutputIterator] (
        InputIterator curves_begin,
        InputIterator curves_end,
        OutputIterator points,
        bool report_endpoint
    )

    OutputIterator compute_subcurves[InputIterator, OutputIterator] (
        InputIterator curves_begin,
        InputIterator curves_end,
        OutputIterator subcurves,
        bool multiple_overlaps
    )

    bool do_curves_intersect[InputIterator] (
        InputIterator curves_begin,
        InputIterator curves_end
    )
