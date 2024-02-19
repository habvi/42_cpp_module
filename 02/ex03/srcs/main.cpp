#include "Point.hpp"
#include <iomanip>
#include <iostream>

#define COLOR_RED   "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_END   "\033[0m"

#define INSIDE      0
#define OUTSIDE     1

static void DisplayTitle(const std::string &title) {
	std::cout << std::endl;
	std::cout << "┃ Test: " << title << std::endl;
	std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << std::endl;
}

static void Line() {
	std::cout << "--------------------------------" << std::endl;
}

static void JudgeIsEqual(const bool result, const bool is_inside) {
	std::cout << (result == is_inside ? COLOR_GREEN "OK" : COLOR_RED "NG")
			  << COLOR_END << std::endl;
}

static void RunBsp(
	const Point &a,
	const Point &b,
	const Point &c,
	const Point &point,
	const bool   is_inside
) {
	std::cout << "a    : (x, y)=(" << a.getX() << ", " << a.getY() << ")"
			  << std::endl;
	std::cout << "b    : (x, y)=(" << b.getX() << ", " << b.getY() << ")"
			  << std::endl;
	std::cout << "c    : (x, y)=(" << c.getX() << ", " << c.getY() << ")"
			  << std::endl;
	std::cout << "point: (x, y)=(" << point.getX() << ", " << point.getY() << ")"
			  << std::endl;
	JudgeIsEqual(bsp(a, b, c, point), is_inside);
	Line();
}

static void RunOriginalTest() {
	DisplayTitle("1");
	// Point a, Point b, Point c, Point point, is_inside_triangle
	RunBsp(Point(1, 2), Point(-3, 5), Point(12, 30), Point(5, 15), true);
	RunBsp(Point(1, 2), Point(-3, 5), Point(12, 30), Point(0, 10), false);
	RunBsp(Point(1, 2), Point(-3, 5), Point(12, 30), Point(0, 9.5), true);
	RunBsp(Point(1, 2), Point(-3, 5), Point(12, 30), Point(10, 30), false);

	DisplayTitle("2");
	RunBsp(Point(1, 1), Point(3, 1), Point(2, 3), Point(1, 1), false);
	RunBsp(Point(1, 1), Point(3, 1), Point(2, 3), Point(1.1, 1), false);
	RunBsp(Point(1, 1), Point(3, 1), Point(2, 3), Point(1.1, 1.1), true);
	RunBsp(Point(1, 1), Point(3, 1), Point(2, 3), Point(2.0, 2.75), true);
	RunBsp(Point(1, 1), Point(3, 1), Point(2, 3), Point(3.0, 1.75), false);

	DisplayTitle("3");
	RunBsp(Point(-10, 4), Point(0, 4), Point(23.4, 4), Point(1.0, 4), false);
	RunBsp(Point(-10, 4), Point(0, 4), Point(23.4, 4), Point(1.0, 4.1), false);
	RunBsp(Point(-10, 4), Point(0, 4), Point(23.4, 4), Point(3.0, 1.75), false);
}

int main() {
	RunOriginalTest();

	return 0;
}
