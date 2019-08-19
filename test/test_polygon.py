import numpy as np
from cgal.dd import Point, Polygon

if __name__ == "__main__":
    points = [Point(0,0), Point(2,0), Point(2,3), Point(1,2)]
    poly = Polygon(points)
    assert poly.area() == 3.5
    assert list(poly.vertices_iterator) == points

    idx = poly.vertices_iterator
    points[0] = Point(-1,0)
    poly.set(idx, points[0])
    points[3] = Point(1,3)
    poly.set(3,   points[3])
    assert poly.area() == 6.
    assert list(poly.vertices_iterator) == points

    points = np.array([(0,0), (2,0), (2,3), (1,2)])
    poly = Polygon(points)
    assert poly.area() == 3.5
