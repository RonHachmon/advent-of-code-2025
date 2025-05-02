package aoc.utils;

/**
 * Represents a direction in a 2D grid.
 */
public class Direction {
    public final int dx;
    public final int dy;

    /**
     * Creates a new direction with the specified deltas.
     *
     * @param dx The change in x-coordinate
     * @param dy The change in y-coordinate
     */
    public Direction(int dx, int dy) {
        this.dx = dx;
        this.dy = dy;
    }

    /**
     * Returns the opposite direction.
     *
     * @return A new Direction representing the opposite direction
     */
    public Direction opposite() {
        return new Direction(-dx, -dy);
    }

    /**
     * Common cardinal and intercardinal directions.
     */
    public static final Direction NORTH = new Direction(-1, 0);
    public static final Direction NORTHEAST = new Direction(-1, 1);
    public static final Direction EAST = new Direction(0, 1);
    public static final Direction SOUTHEAST = new Direction(1, 1);
    public static final Direction SOUTH = new Direction(1, 0);
    public static final Direction SOUTHWEST = new Direction(1, -1);
    public static final Direction WEST = new Direction(0, -1);
    public static final Direction NORTHWEST = new Direction(-1, -1);

    /**
     * Array of all 8 directions (cardinal and intercardinal).
     */
    public static final Direction[] ALL_DIRECTIONS = {
            NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH, SOUTHWEST, WEST, NORTHWEST
    };

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof Direction)) return false;
        Direction other = (Direction) obj;
        return dx == other.dx && dy == other.dy;
    }

    @Override
    public int hashCode() {
        return 31 * dx + dy;
    }

    @Override
    public String toString() {
        return "Direction(" + dx + "," + dy + ")";
    }
}