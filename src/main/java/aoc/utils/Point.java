package aoc.utils;

/**
 * Represents a 2D point with x and y coordinates.
 */
public class Point {
    public final int x;
    public final int y;

    /**
     * Creates a new point with the specified coordinates.
     *
     * @param x The x-coordinate
     * @param y The y-coordinate
     */
    public Point(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * Creates a new point by moving in the specified direction.
     *
     * @param direction The direction to move
     * @return A new Point representing the new position
     */
    public Point move(Direction direction) {
        return new Point(x + direction.dx, y + direction.dy);
    }

    /**
     * Checks if the point is within the bounds of a grid.
     *
     * @param rows Number of rows in the grid
     * @param cols Number of columns in the grid
     * @return true if the point is within bounds, false otherwise
     */
    public boolean isInBounds(int rows, int cols) {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Point)) return false;
        Point other = (Point) obj;
        return x == other.x && y == other.y;
    }

    @Override
    public int hashCode() {
        return 31 * x + y;
    }

    @Override
    public String toString() {
        return "(" + x + "," + y + ")";
    }
}