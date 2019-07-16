cimport cgal.headers.Polygon as C

cdef class Polygon_2:
    cdef C.Polygon_2 base
    @staticmethod
    cdef Polygon_2 wrap(const C.Polygon_2& data)
