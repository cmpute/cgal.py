'''
This file is cython part of cgal_config.h
'''
from libcpp.string cimport string

# Manual type traits
ctypedef double K_FT # FieldNumberType
ctypedef double K_RT # RingNumberType


cdef extern from "cgal_config.h" nogil:
    cdef string to_string_op[T] (const T&)
