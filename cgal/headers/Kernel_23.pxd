from libcpp cimport bool
from cgal.cgal_config cimport K_FT, K_RT

cdef extern from "cgal_config.h" nogil:
    cdef cppclass Origin "CGAL::Origin":
        Point_2 operator+ (const Vector_2&)
        Point_2 operator- (const Vector_2&)
        Vector_2 operator- (const Point_2&)
    cdef Origin ORIGIN "CGAL::ORIGIN"
    cdef cppclass Null_vector "CGAL::Null_vector":
        pass
    cdef Null_vector NULL_VECTOR "CGAL::NULL_VECTOR"
    
    cdef cppclass Point_2:
        Point_2()
        Point_2(const K_FT &x, const K_FT &y)
        Point_2(const K_RT &hx, const K_RT &hy, const K_RT &hw)

        K_FT x()
        K_FT y()
        K_FT cartesian(int i)
        K_FT operator[](int)
        K_RT hx()
        K_RT hy()
        K_RT hw()
        K_RT homogeneous(int i)

        int dimension()

        bool operator==(const Point_2&)
        bool operator!=(const Point_2&)
        bool operator<(const Point_2&)
        bool operator>(const Point_2&)
        bool operator<=(const Point_2&)
        bool operator>=(const Point_2&)
        Vector_2 operator-(const Point_2&)
        Vector_2 operator-(const Origin&)
        Point_2 operator+(const Vector_2&)
        Point_2 operator-(const Vector_2&)
        Point_2& peq "operator+="(const Vector_2&)
        Point_2& seq "operator-="(const Vector_2&)

    cdef cppclass Vector_2:
        Vector_2()
        Vector_2(const Point_2& a, const Point_2& b)
        Vector_2(const K_FT &x, const K_FT &y)
        Vector_2(const K_RT &hx, const K_RT &hy, const K_RT &hw)

        K_FT x()
        K_FT y()
        K_FT cartesian(int i)
        K_FT operator[](int)
        K_RT hx()
        K_RT hy()
        K_RT hw()
        K_RT homogeneous(int i)

        int dimension()
        K_FT squared_length()

        bool operator==(const Vector_2&)
        bool operator!=(const Vector_2&)
        Vector_2 operator+(const Vector_2&)
        Vector_2& peq "operator+="(const Vector_2&)
        Vector_2 operator-()
        Vector_2 operator-(const Vector_2&)
        Vector_2& seq "operator-="(const Vector_2&)
        K_FT operator*(const Vector_2&)
        Vector_2& teq "operator*="(K_RT&)
        Vector_2 operator/(K_RT&)
        Vector_2& deq "operator/="(K_RT&)

    Vector_2 Vector_2_rmul "operator*"(const Vector_2&, const K_RT &)
    Vector_2 Vector_2_rmul "operator*"(const Vector_2&, const K_FT &)
    Vector_2 Vector_2_lmul "operator*"(const K_FT &, const Vector_2&)
    Vector_2 Vector_2_lmul "operator*"(const K_FT &, const Vector_2&)
