import matplotlib.pyplot as plt
from matplotlib.patches import Polygon
import sys

# TRIANGLE_VERTICES : Coordinates of triangle vertices
# TARGET_POINTS     : Coordinates of the target points

def test1():
    global TRIANGLE_VERTICES, TARGET_POINTS

    TRIANGLE_VERTICES = [(1, 2), (-3, 5), (12, 30)]
    TARGET_POINTS = [(5, 15), (0, 10), (0, 9.5), (10, 30)]


def test2():
    global TRIANGLE_VERTICES, TARGET_POINTS

    TRIANGLE_VERTICES = [(1, 1), (3, 1), (2, 3)]
    TARGET_POINTS = [(1, 1), (1.1, 1), (1.1, 1.1), (2.0, 2.75), (3.0, 1.75)]


def test3():
    global TRIANGLE_VERTICES, TARGET_POINTS

    TRIANGLE_VERTICES = [(-10, 4), (0, 4), (23.4, 4)]
    TARGET_POINTS = [(1.0, 4), (1.0, 4.5), (3.0, 1.75)]


# Cross product between each edge of the triangle and the point
def cross_product(a, b, c):
    x1, y1 = a
    x2, y2 = b
    x3, y3 = c
    return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3)


# Determine whether a point is inside the triangle
def is_inside_triangle(point, vertices):
    result1 = cross_product(point, vertices[0], vertices[1])
    result2 = cross_product(point, vertices[1], vertices[2])
    result3 = cross_product(point, vertices[2], vertices[0])

    # If the sign of all cross products is the same, the point is inside the triangle. 
    # If any is 0, it's on a vertex or on edge.
    if (result1 > 0 and result2 > 0 and result3 > 0) or \
        (result1 < 0 and result2 < 0 and result3 < 0):
        return True
    else:
        return False


def main():
    # Plot the triangle
    plt.figure()
    triangle = Polygon(TRIANGLE_VERTICES, closed=True, fill=None, edgecolor='black')
    plt.gca().add_patch(triangle)

    for target in TARGET_POINTS:
        if is_inside_triangle(target, TRIANGLE_VERTICES):
            # Inside: Green
            plt.plot(target[0], target[1], 'go')
        else:
            # Outside: Red
            plt.plot(target[0], target[1], 'ro')

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Triangle and Target Point')
    plt.grid(True)
    plt.axis('equal')
    plt.show()


if __name__ == "__main__":
    if len(sys.argv) > 1 and hasattr(sys.modules[__name__], sys.argv[1]):
        # Execute the function specified by the command line argument
        getattr(sys.modules[__name__], sys.argv[1])()
    main()