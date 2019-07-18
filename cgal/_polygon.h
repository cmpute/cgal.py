#ifndef CGAL_BIND_POLYGON
#define CGAL_BIND_POLYGON

#include "cgal_config.h"
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>

typedef CGAL::Polygon_2<K> Polygon_2;
typedef CGAL::Polygon_with_holes_2<K> Polygon_with_holes_2;

#include <pybind11/stl.h>

#endif // CGAL_BIND_POLYGON
