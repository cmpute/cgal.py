from libcpp cimport bool
from cgal.cgal_config cimport K_FT, K_RT

cdef extern from "cgal_config.h" nogil:
    cppclass Polygon_2[Container_P=*]:
        Polygon_2()
        # Polygon_2[InputIterator](InputIterator, InputIterator)

        