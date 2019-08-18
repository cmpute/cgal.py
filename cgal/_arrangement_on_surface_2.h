#ifndef CGAL_BIND_SURFACE_SWEEP_2
#define CGAL_BIND_SURFACE_SWEEP_2

#include "cgal_config.h"
#include <CGAL/Arrangement_2.h>
#include <CGAL/Arrangement_on_surface_2.h>

#include <CGAL/Arr_segment_traits_2.h>
#include <CGAL/Arr_polyline_traits_2.h>
#include <CGAL/Arr_circle_segment_traits_2.h>

#include <pybind11/stl.h>
#include <memory>

typedef CGAL::Arr_segment_traits_2<K>                   Segment_traits_2;
typedef CGAL::Arr_polyline_traits_2<Segment_traits_2>   Segment_polyline_traits_2;
typedef Segment_polyline_traits_2::Curve_2              Segment_polyline_2;
typedef Segment_polyline_2                              Polyline_2;

typedef CGAL::Arr_circle_segment_traits_2<K>            Circle_traits_2;
typedef CGAL::Arr_polyline_traits_2<Circle_traits_2>    Circle_polyline_traits_2;
typedef Circle_polyline_traits_2::Curve_2               Circle_polyline_2;

#endif // CGAL_BIND_SURFACE_SWEEP_2
