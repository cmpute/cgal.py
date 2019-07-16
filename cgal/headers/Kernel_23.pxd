from libcpp cimport bool
from cgal.cgal_config cimport K_FT, K_RT

cdef extern from "cgal_config.h" nogil:
    ###### Symbolic variables #######
    cppclass Origin "CGAL::Origin":
        Point_2 operator+ (const Vector_2&)
        Point_2 operator- (const Vector_2&)
        Vector_2 operator- (const Point_2&)
    Origin ORIGIN "CGAL::ORIGIN"
    cppclass Null_vector "CGAL::Null_vector":
        pass
    Null_vector NULL_VECTOR "CGAL::NULL_VECTOR"
    #################################

    cppclass Point_2:
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

    cppclass Vector_2:
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

    cppclass Segment_2:
        Segment_2()
        Segment_2(const Point_2& p, const Point_2& q)

        Point_2 source()
        Point_2 target()
        Point_2 min()
        Point_2 max()
        Point_2 vertex(int i)
        Point_2 point(int i)

        K_FT squared_length()
        Vector_2 to_vector()
        Segment_2 opposite()

        bool is_degenerate()
        bool is_horizontal()
        bool is_vertical()
        bool has_on(const Point_2 &p)
        bool collinear_has_on(const Point_2 &p)

        bool operator==(const Segment_2&)
        bool operator!=(const Segment_2&)
        Point_2 operator[](int i)

    # Intersection functions: https://doc.cgal.org/latest/Kernel_23/group__intersection__linear__grp.html
    # TODO: Add more functions
    ctypedef fused _intersect_2_target:
        Point_2
        # Line_2
        # Ray_2
        Segment_2
        # Triangle_2
        # Iso_rectangle_2
    bool do_intersect(_intersect_2_target, _intersect_2_target)
    Point_2 intersection(Segment_2, Segment_2)

