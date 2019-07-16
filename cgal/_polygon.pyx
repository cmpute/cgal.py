cimport cgal.headers.Polygon as C
from cgal.cgal_config cimport K_FT, K_RT

cdef class Polygon_2:
    def __cinit__(self, points):
        pass
    @staticmethod
    cdef Polygon_2 wrap(const C.Polygon_2& data):
        cdef Polygon_2 obj = Polygon_2.__new__(Polygon_2)
        obj.base = data
        return obj
 