#pragma once

namespace aoc {


class Direction {
public:
    /**
     * Rotation angles in degrees.
     */
    enum class Rotation {
        ROTATE_45 = 45,
        ROTATE_90 = 90,
        ROTATE_135 = 135,
        ROTATE_180 = 180,
        ROTATE_225 = 225,
        ROTATE_270 = 270,
        ROTATE_315 = 315
    };


    explicit Direction(int dx = -1, int dy = -1);

    // Static instances of all directions
    static const Direction NORTH;
    static const Direction NORTHEAST;
    static const Direction EAST;
    static const Direction SOUTHEAST;
    static const Direction SOUTH;
    static const Direction SOUTHWEST;
    static const Direction WEST;
    static const Direction NORTHWEST;


    static const Direction* const ALL_DIRECTIONS[8];

    Direction(const Direction& other) = default;
    Direction(Direction&& other) = default;
    Direction& operator=(const Direction& other) =default;
    Direction& operator=(Direction&& other) = default;

    /**
     * Returns the opposite direction.
     *
     * @return The opposite direction instance
     */
    const Direction opposite() const;

    /**
     * Rotates the direction by the specified angle.
     *
     * @param angle The rotation angle
     * @return The direction instance rotated by the specified angle
     */
    void rotate(Rotation angle);

    /**
     * Getters for dx and dy
     */
    int getDx() const { return dx; }
    int getDy() const { return dy; }

    
    bool operator==(const Direction& other) const;
    bool operator!=(const Direction& other) const;

private:
    int dx;
    int dy;
};

} // namespace aoc
