#include "Point.hpp"

namespace aoc {

Point::Point(int x, int y) : x(x), y(y) {}

// Other special member functions are defaulted or deleted in the header file

void Point::move(const Direction& direction) {
    x = x + direction.getDx();
    y = y + direction.getDy();

}

Point Point::moved(const Direction& direction) const {
    return Point(x + direction.getDx(), y + direction.getDy());
}

bool Point::isInBounds(int rows, int cols) const {
    return x >= 0 && x < rows && y >= 0 && y < cols;
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

} // namespace aoc
