cimport cgal.headers.Kernel_23 as C

cdef class ORIGIN:
    pass

cdef class Point_2:
    cdef C.Point_2 base
    @staticmethod
    cdef Point_2 wrap(const C.Point_2& data)

cdef class Vector_2:
    cdef C.Vector_2 base
    @staticmethod
    cdef Vector_2 wrap(const C.Vector_2& data)

cdef class Segment_2:
    cdef C.Segment_2 base
    @staticmethod
    cdef Segment_2 wrap(const C.Segment_2& data)

cpdef intersection(obj1, obj2)
