cimport cgal.headers.Kernel_23 as C
from cgal.cgal_config cimport K_FT, K_RT, to_string_op

cdef class _origin:
    '''
    Symbolic origin. Same as ORIGIN in CGAL
    '''
    def __str__ (self):
        return "ORIGIN"
    def __add__ (x, y):
        if isinstance(x, Vector_2):
            return Point_2.wrap(C.ORIGIN + (<Vector_2>y).base)
        else:
            raise TypeError("Vector_2 or Vector_3 is required")
    def __sub__ (x, y):
        if isinstance(y, Vector_2):
            return Point_2.wrap(C.ORIGIN - (<Vector_2>y).base)
        elif isinstance(y, Point_2):
            return Vector_2.wrap(C.ORIGIN - (<Point_2>y).base)
        else:
            raise TypeError("Point_2, Point_3, Vector_2 or Vector_3 is required")
cdef _origin ORIGIN

cdef class _null_vector:
    '''
    Symbolic null vector. Same as NULL_VECTOR in CGAL
    '''
    def __str__(self):
        return "NULL_VECTOR"
cdef _null_vector NULL_VECTOR

cdef class Point_2:
    def __cinit__(self, x=None, y=None, data=None):
        if x != None and y != None:
            self.base = C.Point_2(<K_FT?>x, <K_FT?>y)
    @staticmethod
    cdef Point_2 wrap(const C.Point_2& data):
        cdef Point_2 obj = Point_2.__new__(Point_2)
        obj.base = data
        return obj

    property x:
        def __get__(self):
            return self.base.x()
    property y:
        def __get__(self):
            return self.base.y()
    property hx:
        def __get__(self):
            return self.base.hx()
    property hy:
        def __get__(self):
            return self.base.hy()
    property hw:
        def __get__(self):
            return self.base.hw()
    property dimension:
        def __get__(self):
            return self.base.dimension()
    def cartesian(self, int idx):
        return self.base.cartesian(idx)
    def homogeneous(self, int idx):
        return self.base.homogeneous(idx)

    def __add__ (Point_2 x, Vector_2 y):
        return Point_2.wrap(x.base + y.base)
    def __sub__ (Point_2 x, y):
        if isinstance(y, Vector_2):
            return Point_2.wrap(x.base - (<Vector_2>y).base)
        elif isinstance(y, Point_2):
            return Vector_2.wrap(x.base - (<Point_2>y).base)
        elif isinstance(y, _origin):
            return Vector_2.wrap(x.base - C.ORIGIN)
        else:
            raise TypeError("Point_2 or Vector_2 or ORIGIN is required")
    def __iadd__ (self, Vector_2 other):
        self.base.peq(other.base)
        return self
    def __isub__ (self, Vector_2 other):
        self.base.seq(other.base)
        return self
    def __lt__(self, Point_2 other):
        return self.base < other.base
    def __le__(self, Point_2 other):
        return self.base <= other.base
    def __eq__(self, Point_2 other):
        return self.base == other.base
    def __ne__(self, Point_2 other):
        return self.base != other.base
    def __gt__(self, Point_2 other):
        return self.base > other.base
    def __ge__(self, Point_2 other):
        return self.base >= other.base
    def __str__(self):
        return to_string_op(self.base).decode('ascii')
    def __getitem__(self, int index):
        return self.base[index]

cdef class Vector_2:
    def __cinit__(self, x=None, y=None, data=None):
        if x != None and y != None:
            self.base = C.Vector_2(<K_FT?>x, <K_FT?>y)
    @staticmethod
    cdef Vector_2 wrap(const C.Vector_2& data):
        cdef Vector_2 obj = Vector_2.__new__(Vector_2)
        obj.base = data
        return obj

    property x:
        def __get__(self):
            return self.base.x()
    property y:
        def __get__(self):
            return self.base.y()
    property hx:
        def __get__(self):
            return self.base.hx()
    property hy:
        def __get__(self):
            return self.base.hy()
    property hw:
        def __get__(self):
            return self.base.hw()
    property dimension:
        def __get__(self):
            return self.base.dimension()
    property squared_length:
        def __get__(self):
            return self.base.squared_length()
    def cartesian(self, int idx):
        return self.base.cartesian(idx)
    def homogeneous(self, int idx):
        return self.base.homogeneous(idx)

    def __add__ (Vector_2 x, Vector_2 y):
        return Vector_2.wrap(x.base + y.base)
    def __sub__ (Vector_2 x, Vector_2 y):
        return Vector_2.wrap(x.base - y.base)
    def __mul__ (x, y):
        if isinstance(x, Vector_2) and isinstance(y, Vector_2):
            return (<Vector_2>x).base * (<Vector_2>y).base
        elif isinstance(x, Vector_2) and isinstance(y, (int, float)):
            return Vector_2.wrap(C.Vector_2_rmul((<Vector_2>x).base, <K_FT>y))
        elif isinstance(x, Vector_2) and isinstance(y, Point_2):
            # Note: this is not declared in original C++ codes
            return Point_2.wrap((<Point_2>y).base + (<Vector_2>x).base)
        elif isinstance(x, (int, float)) and isinstance(y, Vector_2):
            return Vector_2.wrap(C.Vector_2_lmul(<K_FT>x, (<Vector_2>y).base))
        else:
            raise TypeError("Input types are incorrect")
    def __div__(Vector_2 x, K_FT y):
        return Vector_2.wrap(x.base / y)
    def __iadd__ (self, Vector_2 other):
        self.base.peq(other.base)
        return self
    def __isub__ (self, Vector_2 other):
        self.base.seq(other.base)
        return self
    def __imul__ (self, K_FT other):
        self.base.teq(other)
        return self
    def __idiv__ (self, K_FT other):
        self.base.deq(other)
        return self
    def __neg__ (self):
        return Vector_2.wrap(-self.base)
    def __eq__(self, Vector_2 other):
        return self.base == other.base
    def __ne__(self, Vector_2 other):
        return self.base != other.base
    def __str__(self):
        return to_string_op(self.base).decode('ascii')
    def __getitem__(self, int index):
        return self.base[index]

cdef class Segment_2:
    def __cinit__(self, p=None, q=None):
        if p != None and q != None:
            self.base = C.Segment_2((<Point_2?>p).base, (<Point_2?>q).base)
    @staticmethod
    cdef Segment_2 wrap(const C.Segment_2& data):
        cdef Segment_2 obj = Segment_2.__new__(Segment_2)
        obj.base = data
        return obj

    property source:
        def __get__(self):
            return Point_2.wrap(self.base.source())
    property target:
        def __get__(self):
            return Point_2.wrap(self.base.target())
    property min:
        def __get__(self):
            return Point_2.wrap(self.base.min())
    property max:
        def __get__(self):
            return Point_2.wrap(self.base.max())
    property squared_length:
        def __get__(self):
            return self.base.squared_length()
    property is_degenerate:
        def __get__(self):
            return self.base.is_degenerate()
    property is_horizontal:
        def __get__(self):
            return self.base.is_horizontal()
    property is_vertical:
        def __get__(self):
            return self.base.is_vertical()
    def has_on(self, Point_2 p):
        return self.base.has_on(p.base)
    def collinear_has_on(self, Point_2 p):
        return self.base.collinear_has_on(p.base)
    def opposite(self):
        return Segment_2.wrap(self.base.opposite())
    def to_vector(self):
        return Vector_2.wrap(self.base.to_vector())

    def __eq__(self, Segment_2 other):
        return self.base == other.base
    def __ne__(self, Segment_2 other):
        return self.base != other.base
    def __str__(self):
        return to_string_op(self.base).decode('ascii')
    def __getitem__(self, int index):
        return Point_2.wrap(self.base[index])

cpdef intersection(obj1, obj2):
    # TODO: implement this with C++ type definition using a separate file
    # Ideally will be `object result = intersection_(PyObject obj1, PyObject obj2)`
    pass
