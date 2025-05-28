#pragma once
#include <functional>
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
    Direction opposite() const;

    /**
     * Rotates the direction by the specified angle.
     *
     * @param angle The rotation angle
     * @return The direction instance rotated by the specified angle
     */
    void rotate(Rotation angle);

    Direction rotated(Rotation angle) const;

    bool isHorizontal() const { return dx == 0; }

    bool isVertical() const { return dy == 0; }
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


namespace std {
    template <>
    struct hash<aoc::Direction> {
        std::size_t operator()(const aoc::Direction& p) const noexcept {
            std::size_t h1 = std::hash<int>{}(p.getDx());
            std::size_t h2 = std::hash<int>{}(p.getDy());
            return h1 ^ (h2 << 1); // Combine hashes
        }
    };
}
