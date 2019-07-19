from cgal import Point_2 as Point, Polygon_2 as Polygon

if __name__ == "__main__":
    points = [Point(0,0), Point(2,0), Point(2,3), Point(1,2)]
    poly = Polygon(points)
    assert poly.area() == 3.5
    assert list(poly.vertices) == points

    idx = poly.vertices
    points[0] = Point(-1,0)
    poly.set(idx, points[0])
    assert poly.area() == 4.5
    assert list(poly.vertices) == points
