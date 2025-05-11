#pragma once
#include "Direction.hpp"

namespace aoc {

/**
 * Represents a 2D point with x and y coordinates.
 */
class Point {
public:
    /**
     * Creates a new point with the specified coordinates.
     *
     * @param x The x-coordinate
     * @param y The y-coordinate
     */
    explicit Point(int x, int y);

    // Copy constructor
    Point(const Point& other) = default;

    // Move constructor
    Point(Point&& other) noexcept = default;


    Point& operator=(const Point& other) = default;


    Point& operator=(Point&& other) noexcept = default;

    // Destructor
    ~Point() = default;

    /**
     * Creates a new point by moving in the specified direction.
     *
     * @param direction The direction to move
     * @return A new Point representing the new position
     */
    void move(const Direction& direction);

    /**
     * Creates a new point by moving in the specified direction (immutable).
     *
     * @param direction The direction to move
     * @return A new Point representing the new position
     */
    Point moved(const Direction& direction) const;

    inline int getX() const { return x; }
    inline int getY() const { return y; }

    /**
     * Checks if the point is within the bounds of a grid.
     *
     * @param rows Number of rows in the grid
     * @param cols Number of columns in the grid
     * @return true if the point is within bounds, false otherwise
     */
    bool isInBounds(int rows, int cols) const;

    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;

private:
    int x, y;
};

} // namespace aoc
